#ifndef __CRYSTAL_PHYSICS_SPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_SPH_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Polygon/Particle.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;

class SPHParticle final : public Polygon::Particle, private UnCopyable
{
public:
	SPHParticle();

	SPHParticle(const Particle& particle, float pressureCoe = 1.0f, float viscosityCoe = 0.0f);

	SPHParticle(const Math::Vector3d<float>& center, float radius, float density, float pressureCoe = 1.0f, float viscosityCoe = 0.0f);

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce( const Math::Vector3d<float>& force ) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	float getRestDensity() const { return restDensity; }

	void init() {
		density = 0.0;
		force = Math::Vector3d<float>( 0.0f, 0.0f, 0.0f);
	}


	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d<float>& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	float getViscosityCoe() const { return viscosityCoe; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

private:

	float restDensity;
	float density;
	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	float pressureCoe;
	float viscosityCoe;
};

	}
}

#endif