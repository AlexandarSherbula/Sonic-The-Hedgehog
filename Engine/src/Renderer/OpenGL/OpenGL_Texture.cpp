#include "aio_pch.h"

#if defined(AIO_API_OPENGL)
#include "OpenGL_Texture.h"

#include "stb_image/stb_image.h"

namespace Alexio
{
	OpenGL_Texture::OpenGL_Texture(uint32_t width, uint32_t height, uint32_t whiteTexture)
	{
		mWidth = width;
		mHeight = height;

		mInternalFormat = GL_RGBA8;
		mDataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &mID);
		glTextureStorage2D(mID, 1, mInternalFormat, mWidth, mHeight);

		glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(mID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(mID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, &whiteTexture);
	}

	OpenGL_Texture::OpenGL_Texture(const std::string& filepath)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			mWidth = width;
			mHeight = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			mInternalFormat = internalFormat;
			mDataFormat = dataFormat;

			AIO_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &mID);
			glTextureStorage2D(mID, 1, internalFormat, mWidth, mHeight);

			glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(mID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(mID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	OpenGL_Texture::~OpenGL_Texture()
	{
		glDeleteTextures(1, &mID);
	}

	void OpenGL_Texture::SetData(const void* data, uint32_t size)
	{
		uint32_t bpp = mDataFormat == GL_RGBA ? 4 : 3;
		AIO_ASSERT(size == mWidth * mHeight * bpp, "Data must be entire texture!");
		glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGL_Texture::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, mID);
	}

	void OpenGL_Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
#endif