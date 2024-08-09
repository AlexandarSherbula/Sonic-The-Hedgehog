#pragma once

#include "Renderer/Texture.h"

#if defined(AIO_API_OPENGL)
namespace Alexio
{
	class OpenGL_Texture : public Texture
	{
	public:
		OpenGL_Texture(uint32_t width, uint32_t height, uint32_t whiteTexture);
		OpenGL_Texture(const std::string& filepath);

		~OpenGL_Texture();

		void Bind(uint32_t slot) override;
		void Unbind() override;

		void SetData(const void* data, uint32_t size) override;
	private:
		GLenum mInternalFormat, mDataFormat;
	};
}
#endif