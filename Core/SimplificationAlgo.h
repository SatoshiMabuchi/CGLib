#ifndef __CRYSTAL_CORE_SIMPLIFICATION_ALGO_H__
#define __CRYSTAL_CORE_SIMPLIFICATION_ALGO_H__

#include "SurfaceFactory.h"

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class SimplificationAlgo
{
public:

	SimplificationAlgo(Surface* s, SurfaceFactory* f) :
		surface(s),
		factory(f)
	{}

	void execute();

	void execute(Edge* e);

private:
	Surface* surface;
	SurfaceFactory* factory;
};

	}
}
#endif