#include "glfw.h"
#include "IOSample.h"

#include "../IO/STLFile.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::IO;

void IOSample::setup()
{
	STLFile file;
	bool result = file.read("../TestFile/IO/cube-binary.stl");
	assert(result == true);
	polygon.reset(file.toPolygonObject());
}

void IOSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	LineBuffer buffer;
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	buffer.add(*polygon, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0));
	renderer.render(camera, buffer);
}
