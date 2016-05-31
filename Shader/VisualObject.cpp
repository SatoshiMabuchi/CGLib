#include "GLee.h"
#include "VisualObject.h"

#include "../Core/Particle.h"
#include "../Physics/PhysicsObject.h"
#include "../Core/Volume.h"

#include "../Graphics/Light.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Core;

VisualObject::VisualObject(const PolygonMesh& polygon)
{
	pointBuffer.add(polygon);
	lineBuffer.add(polygon, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0));
	triangleBuffer.add(polygon);
}

VisualObject::VisualObject(const PhysicsObject& physics)
{
	const auto& particles = physics.getParticles();
	//pointBuffer.add(*p);
}

VisualObject::VisualObject(const Volume& volume)
{
	const auto& particles = volume.toParticles(0.5f, 0.1f);
	for (const auto& p : particles) {
		pointBuffer.add(p);
	}
}



void VisualObject::renderTriangles(const ICamera<float>& camera)
{
	Graphics::PointLight<float> light;
	light.setPos(Math::Vector3d<float>(-10.0, 10.0, -10.0));
	light.setDiffuse(Graphics::ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));

	renderer.render(camera, light, triangleBuffer);
}
