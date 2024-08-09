#pragma once

#include "Renderer/RendererBackend.h"

#if defined(AIO_API_DX11)
#include <d3d11.h>
#include <wrl/client.h>

struct AdapterData
{
	IDXGIAdapter* ptr = nullptr;
	DXGI_ADAPTER_DESC description;
};

namespace Alexio
{
	class DX11_Backend : public RendererBackend
	{
	public:
		DX11_Backend();
		~DX11_Backend();

		void Initialize() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void Draw(uint32_t vertexCount) override;
		void DrawIndexed(uint32_t indexCount) override;
		void Clear(float r, float g, float b, float a) override;
		void CreateRenderTarget();
		void CleanRenderTarget();
		void SwapBuffer() override;

		// Getters
		inline ID3D11Device* GetDevice() const { return mDevice.Get(); }
		inline ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext.Get(); }
		inline IDXGISwapChain* GetSwapChain() const { return mSwapChain.Get(); }
		inline std::string GetName() const override { return "DirectX 11"; }
	private:
		void ImGuiBackendInit() override;
		void ImGuiBackendBegin() override;
		void ImGuiBackendUpdate() override;
		void ImGuiBackendShutDown() override;
	private:
		static DX11_Backend* sInstance;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
		Microsoft::WRL::ComPtr<ID3D11BlendState> mBlendState;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState;
	};

	std::string ResultInfo(HRESULT hr);
}
#endif