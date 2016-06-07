#ifndef __CRYSTAL_MATH_CURVE_3D_H__
#define __CRYSTAL_MATH_CURVE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Curve3d
{
public:
	Curve3d();

	Curve3d(const int uNum, const int vNum);

	Vector3d<T> getPosition(const int u, const int v) const;

	void setPosition(const int u, const int v, const Vector3d<T>& pos);

	int getUNumber() const { return uNumber; }

	int getVNumber() const { return vNumber; }

private:
	std::vector< std::vector< Vector3d<T> > > positions;
	std::vector< std::vector< Vector3d<T> > > normals;
	int uNumber;
	int vNumber;
};
	}
}


#endif