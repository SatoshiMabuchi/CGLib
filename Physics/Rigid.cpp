#include "Rigid.h"

#include "../Math/Quaternion.h"
#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Rigid::Rigid()
{}

Rigid::Rigid(const std::vector<SPHParticle*>& particles) :
	PhysicsObject(particles)
{
}

void Rigid::coordinate(const float timeStep)
{
	const auto& particles = getParticles();
	const auto& objectCenter = getCenter();
	const auto& velocityAverage = getAverageVelosity();

	setVelocity(velocityAverage);

	move(-1.0 * objectCenter);

	//assert( getCenter( particles ) == Math::Vector3d( 0.0, 0.0, 0.0 ) );

	Math::Vector3d<float> inertiaMoment(0.0, 0.0, 0.0);
	Math::Vector3d<float> torque(0.0, 0.0, 0.0);

	for (const auto& particle : particles) {
		const auto& center = particle->getPosition();

		Math::Vector3d<float> particleMoment(pow(center.getY(), 2) + pow(center.getZ(), 2),
			pow(center.getZ(), 2) + pow(center.getX(), 2),
			pow(center.getX(), 2) + pow(center.getY(), 2));
		inertiaMoment += (particleMoment)* particle->getMass();

		const Math::Vector3d<float> diffVector(Math::Vector3d<float>(0.0, 0.0, 0.0), particle->getPosition());
		const Math::Vector3d<float>& particleTorque = diffVector.getOuterProduct(particle->getForce() * particle->getVolume());
		torque += particleTorque;
	}

	getAngleVelosity(inertiaMoment, torque, timeStep);

	if (Math::Tolerance<float>::isEqualStrictly(angleVelosity.getLength())) {
		move(objectCenter);
		convertToFluidForce();
		return;
	}
	const float rotateAngle = angleVelosity.getLength() * timeStep;
	if (rotateAngle < 1.0e-5) {
		move(objectCenter);
		convertToFluidForce();
		return;
	}

	Math::Quaternion<float> quaternion(angleVelosity.getNormalized(), rotateAngle);
	const auto& rotateMatrix = quaternion.toMatrix();
	for( const auto& p : particles ) {
		p->rotate( rotateMatrix );
	}

	move(objectCenter);
	convertToFluidForce();
}


void Rigid::getAngleVelosity(const Vector3d<float>& I, const Vector3d<float>& N, const float proceedTime)
{
	float x1, x2, x3;
	const int innerSteps = 10;
	float h = proceedTime / innerSteps;

	x1 = angleVelosity.getX();
	x2 = angleVelosity.getY();
	x3 = angleVelosity.getZ();

	for (int i = 0; i < innerSteps; i++) {
		const float k11 = h * getAngleAccelerationX(x1, x2, x3, I, N);
		const float k21 = h * getAngleAccelerationY(x1, x2, x3, I, N);
		const float k31 = h * getAngleAccelerationZ(x1, x2, x3, I, N);
		const float k12 = h * getAngleAccelerationX(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
		const float k22 = h * getAngleAccelerationY(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
		const float k32 = h * getAngleAccelerationZ(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
		const float k13 = h * getAngleAccelerationX(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
		const float k23 = h * getAngleAccelerationY(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
		const float k33 = h * getAngleAccelerationZ(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
		const float k14 = h * getAngleAccelerationX(x1 + k13, x2 + k23, x3 + k33, I, N);
		const float k24 = h * getAngleAccelerationY(x1 + k13, x2 + k23, x3 + k33, I, N);
		const float k34 = h * getAngleAccelerationZ(x1 + k13, x2 + k23, x3 + k33, I, N);

		const float dx1 = (k11 + 2.0f * k12 + 2.0f * k13 + k14) / 6.0f;
		const float dx2 = (k21 + 2.0f * k22 + 2.0f * k23 + k24) / 6.0f;
		const float dx3 = (k31 + 2.0f * k32 + 2.0f * k33 + k34) / 6.0f;

		x1 += dx1;
		x2 += dx2;
		x3 += dx3;
	}

	angleVelosity = Math::Vector3d<float>(x1, x2, x3);
}

float Rigid::getAngleAccelerationX(float x1, float x2, float x3, const Vector3d<float>& I, const Vector3d<float>& N)
{
	return (N.getX() + (I.getY() - I.getZ()) * x2 * x3) / I.getX() - 10.0f * x1;
}

float Rigid::getAngleAccelerationY(float x1, float x2, float x3, const Vector3d<float>& I, const Vector3d<float>& N)
{
	return (N.getY() + (I.getZ() - I.getX()) * x3 * x1) / I.getY() - 10.0f * x2;
}

float Rigid::getAngleAccelerationZ(float x1, float x2, float x3, const Vector3d<float>& I, const Vector3d<float>& N)
{
	return (N.getZ() + (I.getX() - I.getY()) * x1 * x2) / I.getZ() - 10.0f * x3;
}