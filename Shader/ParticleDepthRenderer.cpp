#include "ParticleDepthRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool ParticleDepthRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string ParticleDepthRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec3 position;" << std::endl;
	stream << "in float pointSize;" << std::endl;
	stream << "out float vDepth;" << std::endl;
	stream << "out float vSize;" << std::endl;
	stream << "out vec4 vPosition;" << std::endl;
	stream << "uniform mat4 projectionMatrix;" << std::endl;
	stream << "uniform mat4 modelviewMatrix;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl;
	stream << "gl_PointSize = pointSize / gl_Position.w;" << std::endl;
	stream << "vDepth = gl_Position.z; // / gl_Position.w;" << std::endl;
	stream << "vSize = gl_PointSize;" << std::endl;
	stream << "vPosition = gl_Position;" << std::endl;
	stream << "}" << std::endl;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string ParticleDepthRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "out vec4 fragColor;" << std::endl;
	stream << "in float vDepth;" << std::endl;
	stream << "in float vSize;" << std::endl;
	stream << "in vec4 vPosition;" << std::endl;
	stream << "uniform float near;" << std::endl;
	stream << "uniform float far;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "vec3 coord;" << std::endl;
	stream << "coord.xy = gl_PointCoord * 2.0 - 1.0;" << std::endl;
	stream << "float distSquared = dot(coord.xy, coord.xy);" << std::endl;
	stream << "if (distSquared > 1.0) {" << std::endl;
	stream << "		discard;" << std::endl;
	stream << "}" << std::endl;
	stream << "coord.z = -sqrt(1.0 - distSquared);" << std::endl;
	stream << "float thickness = coord.z / (far - near) + vDepth / (far - near);" << std::endl;
	stream << "vec3 depth = vec3(thickness);" << std::endl;// vPosition.w;//gl_FragDepth);// + sqrt(distSquared);" << std::endl;
	//stream << "depth = vec3(vDepth);" << std::endl;// / vPosition.w;//gl_FragDepth);// + sqrt(distSquared);" << std::endl;

	stream << "fragColor.rgb = depth;" << std::endl;
	stream << "fragColor.a = 1.0;" << std::endl;
	stream << "}" << std::endl;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void ParticleDepthRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findUniformLocation("near");
	shader.findUniformLocation("far");

	shader.findAttribLocation("position");
	shader.findAttribLocation("pointSize");
}


void ParticleDepthRenderer::render(const ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_DEPTH_TEST);


	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);


	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDepthMask(GL_FALSE);
	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform1f(shader.getUniformLocation("near"), camera.getNear());
	glUniform1f(shader.getUniformLocation("far"), camera.getFar());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}