#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

#include "Window/Window.h"

namespace Alexio
{
	class RendererBackend
	{
	public:
		virtual ~RendererBackend() = default;

		static Ref<RendererBackend> Create();

		virtual void Initialize() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Draw(uint32_t vertexCount) = 0;
		virtual void DrawIndexed(uint32_t indexCount) = 0;
		virtual void Clear(float r, float g, float b, float a) = 0;
		virtual void SwapBuffer() = 0;

		virtual void ImGuiBackendInit() = 0;
		virtual void ImGuiBackendBegin() = 0;
		virtual void ImGuiBackendUpdate() = 0;
		virtual void ImGuiBackendShutDown() = 0;

		virtual std::string GetName() const = 0;

		inline void SetVSync(bool vSync) { mVSync = vSync; }
		inline bool IsVSync() const { return mVSync; }
		
		inline static void SetGraphicsAPI(GraphicsAPI api) { sAPI = api; }
		inline static GraphicsAPI GetGraphicsAPI() { return sAPI; }
	protected:
		bool mVSync;
	private:
		static GraphicsAPI sAPI;
	};
}