#ifndef __CRYSTAL_SHADER_FRAME_BUFFER_H__
#define __CRYSTAL_SHADER_FRAME_BUFFER_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "TextureObject.h"
#include "DepthTextureObject.h"
#include <cassert>
#include <vector>

namespace Crystal {
	namespace Shader {

class FrameBuffer
{
public:
	~FrameBuffer() {
		unbind();
	}

	void build(int width, int height);

	void setTexture(const TextureObject& texture);

	void bind();

	void unbind();

	Graphics::Image toImage() const;

	Graphics::ColorRGBA<unsigned char> getColor(const int x, const int y) const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	GLuint frameBuffer;
	int width;
	int height;
};
	}
}

#endif
