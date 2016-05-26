#include "Cone.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cone<T>::Cone() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height) :
	radius(radius),
	height(height)
{}

template<typename T>
T Cone<T>::getVolume() const
{
	return Tolerance<T>::getPI() * radius * radius * height / T{ 3 };
}

template class Cone<float>;
template class Cone<double>;