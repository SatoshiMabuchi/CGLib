#ifndef __CRYSTAL_CORE_SURFACE_FACTORY_H__
#define __CRYSTAL_CORE_SURFACE_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {
		class Surface;

class SurfaceFactory : private UnCopyable
{
public:
	SurfaceFactory() = default;

	SurfaceFactory(NodeCollection& nodes, EdgeCollection& edges, FaceCollection_& faces);

	~SurfaceFactory();

	void clear();

	Surface* create(const Math::Curve3d<float>& curve, const int id = -1);

	Surface* create(const Math::CircularCurve3d<float>& curve, const int id = -1);

	Surface* create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

	Face* createTriangleFace(Node* n1, Node* n2, Node* n3);

	//void remove(Node* n);

	void merge(SurfaceFactory& rhs);

	Surface* findSurfaceById(const int id);

	Edge* findEdgeById(const int id) const;

	Node* findNodeById(const int id) const;

	Face* findFaceById(const int id) const;

	std::list<Surface*> getSurfaces() const { return surfaces; }

private:

	Surface* create(int id);

	NodeCollection nodes;
	EdgeCollection edges;
	FaceCollection_ faces;
	std::list<Surface*> surfaces;
};


	}
}

#endif