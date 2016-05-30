#include "Actor.h"
#include "Particle.h"
#include "ParticleObject.h"
#include "Joint.h"
#include "Bone.h"
#include "BoneTree.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;



Actor::Actor() :
	nextBoneId(0),
	nextJointId(0)
{}

Actor::Actor(const std::string& name) :
	name(name),
	nextBoneId(0),
	nextJointId(0)
{
}

void Actor::clear()
{
	for (auto b : bones) {
		delete b;
	}
	bones.clear();
	for (auto j : joints) {
		delete j;
	}
	joints.clear();
	nextBoneId = 0;
	nextJointId = 0;
}


Joint* Actor::createJoint(const Vector3d<float>& pos, const float radius)
{
	auto j = new Joint(pos, radius, nextJointId++);
	joints.push_back(j);
	return j;
}

Joint* Actor::insertJoint(Bone* bone)
{
	auto j1 = bone->getOriginJoint();
	auto j2 = bone->getDestJoint();
	const auto& pos = j1->getPosition() / 2.0f + j2->getPosition() / 2.0f;
	const auto radius = j1->getRadius() / 2.0f + j2->getRadius() / 2.0f;
	auto j = createJoint(pos, radius);
	bones.remove(bone);
	auto b1 = createBone(j1, j);
	auto b2 = createBone(j, j2);
	return j;
}



Bone* Actor::createBone(Joint* j1, Joint* j2)
{
	auto b = new Bone(j1, j2, nextBoneId++);
	bones.push_back(b);
	return b;
}

void Actor::remove(Joint* j)
{
	std::vector<Bone*> removeBones;
	for (auto b : bones) {
		if (b->getOriginJoint() == j) {
			removeBones.push_back(b);
		}
	}
	Bone* originBone = nullptr;
	for (auto b : bones) {
		if (b->getDestJoint() == j) {
			originBone = b;
		}
	}
	for (auto b : removeBones) {
		originBone->changeDest(b->getDestJoint());
		bones.erase( std::remove(bones.begin(), bones.end(), b) , bones.end());
		delete b;
	}
	joints.erase(std::remove(joints.begin(), joints.end(), j), joints.end());
	delete j;
}


ParticleObject* Actor::toParticleObject(const float divideLength, const float density) const
{
	std::vector<Particle*> particles;
	for (auto j : joints) {
		particles.push_back( j->toParticle(density).clone() );
	}
	for (auto b : bones) {
		if (b->isTail()) {
			continue;
		}
		const auto& ps = b->toParticles(divideLength, density);
		for (const auto& p : ps) {
			particles.push_back( p.clone() );
		}
	}
	return new ParticleObject( particles );
}

Joint* Actor::findJointById(const unsigned int id) const
{
	for (auto j : joints) {
		if (j->getId() == id) {
			return j;
		}
	}
	return nullptr;
}

Bone* Actor::findBoneById(const unsigned int id) const
{
	for (auto b : bones) {
		if (b->getId() == id) {
			return b;
		}
	}
	return nullptr;
}
