#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Polygon {

class Vertex;
class TriangleFace;

class Vertex
{
public:
	Vertex(const Math::Vector3d<float>& position, const unsigned int id) :
		position(position),
		id(id)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Vector3d<float> getNormal() const { return normal; }

	unsigned int getId() const { return id;  }

	void setFace(TriangleFace* f);

	TriangleFace* getFace() { return f; }

	unsigned int id;

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> normal;
	TriangleFace* f;
};


class TriangleMesh : private UnCopyable
{
public:
	TriangleMesh() :
		nextIndexId(0)
	{}

	~TriangleMesh();

	bool hasVertex(Vertex* v);

	void clear();

	void sortVertices();

	Vertex* createVertex(const Math::Vector3d<float>& position);

	Vertex* createVertexIfNotThere(const Math::Vector3d<float>& position);


	//void addVertex(Vertex* v) { this->vertices.push_back(v); }

	TriangleFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	std::list<Vertex*> getVertices() const { return vertices; }

	std::vector<TriangleFace*> getFaces() const { return faces; }

	TriangleMesh* clone() {
		auto newMesh = new TriangleMesh;
		newMesh->vertices = this->vertices;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->faces.clear();
		return newMesh;
	}

private:
	unsigned int nextIndexId;
	std::list<Vertex*> vertices;
	std::vector<TriangleFace*> faces;
};


	}
}
#endif