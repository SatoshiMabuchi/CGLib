#ifndef __CRYSTAL_SHADER_ON_SCREEN_RENDERER_H__
#define __CRYSTAL_SHADER_ON_SCREEN_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class OnScreenRenderer
{
public:
	void render(const Texturef& texture, const float alpha);

	bool build();

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject shader;
};

	}
}

#endif