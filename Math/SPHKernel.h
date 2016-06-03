#ifndef __CRYSTAL_MATH_SPH_KERNEL_H__
#define __CRYSTAL_MATH_SPH_KERNEL_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace Math {

template<typename T, typename int DIM = 3>
class SPHKernel
{
public:
	SPHKernel() = default;

	float getPoly6Kernel(const T distance, const T effectLength);

	Math::Vector3d<T> getPoly6KernelGradient(const Math::Vector3d<T>& distanceVector, const T effectLength);

	float getPoly6KernelLaplacian(const T distance, const T effectLength);

	Math::Vector3d<T> getSpikyKernelGradient(const Math::Vector3d<T> &distanceVector, const float effectLength);

	float getViscosityKernelLaplacian(const T distance, const T effectLength);

	T getCubicSpline(const T q);

	T getCubicSpline(const Vector3d<T>& v, const T effectLength);

	T getCubicSpline(const Vector3d<T>& v, const Matrix3d<T>& m);
};
	}
}

#endif