#include "gtest\gtest.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;

TEST(SPHKernelTest, TestGetCubicSpiline)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(0);
		const auto expected = 1.0f / Tolerance<float>::getPI();
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(1);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(2);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
}

TEST(SPHKernelTest, TestGetCubicSpilineByVector)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(1, 0, 0), 1.0f);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), 1.0f);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

	{
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), 2.0f);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI()) / 8;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

}

TEST(SPHKernelTest, TestGetCubicSpilineByMatrix)
{
	SPHKernel<float> kernel;
	{
		Matrix3d<float> matrix;
		const auto actual = kernel.getCubicSpline(Vector3d<float>(1, 0, 0), matrix);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		Matrix3d<float> matrix;
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), matrix);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

	{
		Matrix3d<float> matrix = Vector3d<float>(0.5, 0.5, 0.5).toDiagonalMatrix();
		const auto actual = kernel.getCubicSpline(Vector3d<float>(2, 0, 0), matrix);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI()) / 8;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
}