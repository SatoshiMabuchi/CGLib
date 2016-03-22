#include "BulletWorld.h"
#include "BulletRigid.h"
#include "BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletWorld::BulletWorld():
	dispatcher(&collisionConfig)
{
	world = new btDiscreteDynamicsWorld(&dispatcher, &overlappingPairCache, &solver, &collisionConfig);
}

void BulletWorld::add(BulletRigid* rigid)
{
	world->addRigidBody(rigid->getBody());
	rigids.push_back(rigid);
}

void BulletWorld::setExternalForce(const Vector3d<float>& f)
{
	world->setGravity(BulletConverter::convert(f));
}

void BulletWorld::simulate(const float timeStep)
{
	world->stepSimulation(timeStep, 10);
}