#ifndef __CRYSTAL_SHADER_FLUID_RENDERER_H__
#define __CRYSTAL_SHADER_FLUID_RENDERER_H__

#include "ParticleDepthRenderer.h"
#include "FrameBuffer.h"
#include "NormalFilter.h"
#include "PointRenderer.h"
#include "BilateralFilter.h"
#include "AbsorptionRenderer.h"
#include "DeferredRenderer.h"
#include "OnScreenRenderer.h"
#include "CubeMapTexture.h"
#include "SSCubeMapRenderer.h"
#include "SkyBoxRenderer.h"
#include "ThicknessRenderer.h"
#include "DepthBuffer.h"

namespace Crystal {
	namespace Shader {

class FluidRenderer
{
public:
	void build(const int width, const int height);

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer, const Graphics::PointLight<float>& light, const Graphics::Material& material, const CubeMapTexture& cubeMapTexture);

	DepthTexture* getDepthTexture() { return depthBuffer.getTexture(); }

	Texturef* getBluredTexture1() { return bluredBuffer1.getTexture(); }

	Texturef* getBluredTexture2() { return bluredBuffer2.getTexture(); }

	Texturef* getVolumeTexture() { return volumeBuffer.getTexture(); }

	Texturef* getCubeMapTexture() { return cubeMapBuffer.getTexture(); }

	Texturef* getThicknessTexture() { return volumeBuffer.getTexture(); }

	Texturef* getNormalTexture() { return normalBuffer.getTexture(); }

private:
	ParticleDepthRenderer depthRenderer;
	DepthBuffer depthBuffer;

	NormalFilter normalFilter;
	FrameBufferf normalBuffer;

	ThicknessRenderer thicknessRenderer;
	FrameBufferf volumeBuffer;
	FrameBufferf bluredVolumeBuffer;

	FrameBufferf shadedBuffer;
	
	BilateralFilter bilateralFilter;
	FrameBufferf bluredBuffer1;
	FrameBufferf bluredBuffer2;

	AbsorptionRenderer absorptionRenderer;
	FrameBufferf absorptionBuffer;

	DeferredRenderer deferredRenderer;
	OnScreenRenderer onScreenRenderer;
	SSCubeMapRenderer cubeMapRenderer;
	FrameBufferf cubeMapBuffer;

	SkyBoxRenderer skyBoxRenderer;

	FrameBufferf backgroundBuffer;

	FrameBufferf fluidBuffer;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif