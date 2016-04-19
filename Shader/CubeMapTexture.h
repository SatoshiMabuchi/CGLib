#ifndef __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_H__
#define __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_H__

#include "../Graphics/Image.h"
#include <array>

namespace Crystal {
	namespace Shader {

class CubeMapTexture
{
public:
	void create(const std::array<Graphics::Imagef, 6>& images, const unsigned int id);

	void setPositiveX(const Graphics::Imagef& image);

	void setNegativeX(const Graphics::Imagef& image);

	void setPositiveY(const Graphics::Imagef& image);

	void setNegativeY(const Graphics::Imagef& image);

	void setPositiveZ(const Graphics::Imagef& image);

	void setNegativeZ(const Graphics::Imagef& image);


	void bind() const;

	void unbind() const;

	unsigned int getId() const { return id; }
private:
	unsigned int texHandle;
	unsigned int id;
};

	}
}

#endif