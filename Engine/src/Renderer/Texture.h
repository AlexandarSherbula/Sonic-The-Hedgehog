#pragma once

namespace Alexio
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		inline uint32_t GetWidth() { return mWidth; }
		inline uint32_t GetHeight() { return mHeight; }
		inline uint32_t GetID() { return mID; }

		virtual void Bind(uint32_t slot) = 0;
		virtual void Unbind() = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Ref<Texture> Create(uint32_t width, uint32_t height, uint32_t whiteTexture = 0xffffffff);
		static Ref<Texture> Create(const std::string& filepath);
	protected:
		uint32_t mID;
		uint32_t mWidth, mHeight;
	};
}