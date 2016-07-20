#include "stdafx.h"

#include "../Core/EdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeCollectionTest, TestNumber)
{
	Vertex v1(Vector3d<float>(0,0,0));
	Vertex v2(Vector3d<float>(1,0,0));

	Edge e1(&v1, &v2);
	Edge e2(&v2, &v1);
	std::list<Edge*> es = { &e1, &e2 };
	EdgeCollection edges(es);
	EXPECT_EQ( &e2, edges.findReverse(&e1) );
}