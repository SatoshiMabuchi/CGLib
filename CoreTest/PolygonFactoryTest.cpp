#include "stdafx.h"

#include "../Core/PolygonFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonFactoryTest, TestMerge)
{
	 Triangle3d<float> t1(Vector3d<float>(-1,0,0), Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	 PolygonFactory f1;
	 f1.create(t1.toCurve3d());
	 PolygonFactory f2;
	 f2.create(t1.toCurve3d());
	 f1.merge(f2);
	 EXPECT_EQ(2, f1.getFaces().size());
	 EXPECT_EQ(0, f2.getFaces().size());
	 EXPECT_EQ(6, f1.getVertices().size());
	 EXPECT_EQ(0, f2.getVertices().size());

}
