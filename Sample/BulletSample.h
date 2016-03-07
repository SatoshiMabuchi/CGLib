#ifndef __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__

#include "glfw.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "ISample.h"

class BulletSample : public ISample
{
public:
	BulletSample();

	~BulletSample();

	void setup() override;

	void demonstrate() override;

	void cleanup() override;

private:
	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;
	btDiscreteDynamicsWorld world;
	btRigidBody* rigid;
};

#endif
