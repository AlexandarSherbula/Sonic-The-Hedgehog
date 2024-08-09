#pragma once

#include "Renderer/Texture.h"
#if defined(AIO_API_DX11)

namespace Alexio
{
	class DX11_Texture : public Texture
	{
	public:
		DX11_Texture(uint32_t width, uint32_t height, uint32_t whiteTexture);
		DX11_Texture(const std::string& filepath);
		~DX11_Texture();

		void Bind(uint32_t slot) override;
		void Unbind() override;

		void SetData(const void* data, uint32_t size) override;
	private:
		static uint32_t sID;
	private:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> mSamplerState;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTextureResource;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTextureBuffer;
	};
}
#endif