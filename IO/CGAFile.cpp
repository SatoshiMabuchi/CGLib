#include "CGAFile.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::IO;

namespace {
	const int fileFormatVersion = 1;
}

bool CGAFile::read(const File& file)
{
	std::ifstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool CGAFile::read(std::istream& stream)
{
	std::string title;
	stream >> title;
	if (title != "CGStudioActorFile") {
		return false;
	}
	int fileFormatVersion = 0;
	stream >> fileFormatVersion;
	if (fileFormatVersion != 1) {
		return false;
	}
	int actorCount = 0;
	stream >> actorCount;
	for (int i = 0; i < actorCount; ++i) {
		Actor* actor = new Actor();
		std::string name;
		stream >> name;
		int jointCount = 0;
		stream >> jointCount;
		std::vector<Joint*> joints;
		for (int j = 0; j < jointCount; ++j) {
			float posx = 0;
			stream >> posx;
			float posy = 0;
			stream >> posy;
			float posz = 0;
			stream >> posz;
			float radius = 0;
			stream >> radius;
			auto joint = actor->createJoint(Vector3d<float>(posx, posy, posz), radius);
			joints.push_back(joint);
		}
		int boneCount = 0;
		stream >> boneCount;
		for (int j = 0; j < boneCount; ++j) {
			int originalJointId = 0;
			stream >> originalJointId;
			int destJointId = 0;
			stream >> destJointId;
			actor->createBone(joints[originalJointId], joints[destJointId]);
		}
		actors.push_back(actor);
	}
	//stream << actor.getBones().size() << std::endl;
	return stream.good();
}

bool CGAFile::write(const File& file)
{
	std::ofstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	return write(stream);
}

bool CGAFile::write(std::ostream& stream)
{
	stream << "CGStudioActorFile" << std::endl;
	stream << fileFormatVersion << std::endl;

	stream << actors.size() << std::endl;
	for (auto& actor : actors) {
		assert(!actor->getName().empty());
		stream << actor->getName() << std::endl;
		const auto& joints = actor->getJoints();
		stream << joints.size() << std::endl;
		for (auto j : joints) {
			stream
				<< j->getPosition().getX() << ","
				<< j->getPosition().getY() << ","
				<< j->getPosition().getZ() << ","
				<< j->getRadius() << std::endl;
		}
		const auto& bones = actor->getBones();
		stream << bones.size() << std::endl;
		for (auto b : bones) {
			stream
				<< b->getOriginJoint()->getId() << ","
				<< b->getDestJoint()->getId() << std::endl;
		}
	}
	return stream.good();

}
