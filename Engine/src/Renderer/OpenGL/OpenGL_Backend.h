#pragma once

#include "Renderer/RendererBackend.h"

#if defined(AIO_API_OPENGL)
namespace Alexio
{
	class OpenGL_Backend : public RendererBackend
	{
	public:
		OpenGL_Backend();
		~OpenGL_Backend();

		void Initialize() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void Draw(uint32_t vertexCount) override;
		void DrawIndexed(uint32_t indexCount) override;
		void Clear(float r, float g, float b, float a) override;
		void SwapBuffer() override;

		inline std::string GetName() const override { return "OpenGL 4.5"; };
	private:
		void ImGuiBackendInit() override;
		void ImGuiBackendBegin() override;
		void ImGuiBackendUpdate() override;
		void ImGuiBackendShutDown() override;

	private:
		static OpenGL_Backend* sInstance;
	private:
	};
}
#endif