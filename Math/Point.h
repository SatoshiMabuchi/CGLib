#ifndef __CRYSTAL_MATH_POINT_H__
#define __CRYSTAL_MATH_POINT_H__

#include "Vector2d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Point
{
public:
	Point() = default;

	explicit Point(const Vector3d<T>& position);

	Point(const Vector3d<T>& position, const Vector3d<T>& normal);

	Point(const Vector3d<T>& position, const Vector3d<T>& normal, const Vector2d<T>& parameter);

	virtual ~Point() {};

	Vector3d<T> getPosition() const { return position; }

	void setNormal(const Math::Vector3d<T>& n) { this->normal = n; }

	Vector3d<T> getNormal() const { return normal; }

	Vector2d<T> getParameter() const { return parameter; }

private:
	Math::Vector3d<T> position;
	Math::Vector3d<T> normal;
	Math::Vector2d<T> parameter;
};
	}
}

#endif