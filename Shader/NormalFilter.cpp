#include "NormalFilter.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool NormalFilter::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string NormalFilter::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec2 position;" << std::endl
		<< "out vec2 texCoord;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	texCoord = position;" << std::endl
		<< "	gl_Position = vec4(texCoord, 0.0, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string NormalFilter::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D depthTex;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform float texelSize;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "vec3 uvToEye(vec2 tCoord, float depth) {" << std::endl
		<< "	vec2 xy = tCoord*2.0 - vec2(1.0,1.0);" << std::endl
		<< "	vec4 clippingPosition = vec4(xy, depth, 1.0);" << std::endl
		<< "	vec4 viewPosition = inverse(projectionMatrix) * clippingPosition;" << std::endl
		<< "    return viewPosition.xyz / viewPosition.w;" << std::endl
		<< "}" << std::endl
		<< "float getDepth(vec2 tCoord){" << std::endl
		<< "	return texture2D(depthTex, tCoord).r;" << std::endl
		<< "}" << std::endl
		<< "vec3 getEyePosition(vec2 texCoord){"
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	return uvToEye(texCoord, depth);" << std::endl
		<< "}" << std::endl
		<< "void main(void) {" << std::endl
		<< "    vec3 eyePosition = getEyePosition(texCoord);" << std::endl
		<< "	vec3 ddx1 = getEyePosition(texCoord + vec2(texelSize, 0)) - eyePosition;" << std::endl
		<< "	vec3 ddx2 = eyePosition - getEyePosition(texCoord-vec2(texelSize, 0));" << std::endl
		<< "	if(abs(ddx1.z) > abs(ddx2.z)) {" << std::endl
		<< "		ddx1 = ddx2;" << std::endl
		<< "	}" << std::endl
		<< "	vec3 ddy1 = getEyePosition(texCoord + vec2(0, texelSize)) - eyePosition;" << std::endl
		<< "	vec3 ddy2 = texCoord - getEyePosition(texCoord - vec2(0, texelSize));" << std::endl
		<< "	if(abs(ddy1.z) > abs(ddy2.z)) {" << std::endl
		<< "		ddy1 = ddy2;" << std::endl
		<< "	}" << std::endl
		<< "	vec3 normal = normalize( cross(ddx1, ddy1) );" << std::endl
		<< "	fragColor.rgb = normal;" << std::endl
		<< "	fragColor.rg = texCoord;" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "	}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void NormalFilter::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("depthTex");
	shader.findUniformLocation("texelSize");
	shader.findAttribLocation("position");
}

void NormalFilter::render(const Texture<unsigned char>& texture, const ICamera<float>& renderedCamera)
{
	/*
	const std::array<Vector2d<float>, 3> positions = {
		Vector2d<float>(-0.5f, 0.5f),
		Vector2d<float>(-0.5f, -0.5f),
		Vector2d<float>(0.5f, -0.5f)//,
		//Vector3d<float>(0.5f, 0.5f, 0.0f),
	};
	*/
	std::vector<float> positions;
	positions.push_back(-1.0f);
	positions.push_back(1.5f);
	positions.push_back(-1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);

	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());
	
	//glGetUniformLocation( texture.getId()
	glUniform1i(shader.getUniformLocation("depthTex"), 0);
	glUniform1f(shader.getUniformLocation("texelSize"), 1.0f / 512.0f);
	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, renderedCamera.getProjectionMatrix().toArray().data());
	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}