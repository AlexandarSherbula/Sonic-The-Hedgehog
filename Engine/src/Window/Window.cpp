#include "aio_pch.h"

#include "GLFW_Window.h"
#include "Win32_Window.h"

#include "Renderer/Renderer.h"

namespace Alexio
{
    Window::~Window()
    {
    }

    Ref<Window> Window::Create(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen)
    {
#if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
        switch (Renderer::GetGraphicsAPI())
        {
            case OpenGL:  return CreateRef<GLFW_Window>(title, width, height, pixelSize, fullscreen);
            case DirectX11: return CreateRef<Win32_Window>(title, width, height, pixelSize, fullscreen);
        }
#elif defined(AIO_API_OPENGL)
        return std::make_shared<GLFW_Window>(title, width, height, pixelSize, fullscreen);
#elif defined(AIO_API_DX11)
        return CreateRef<Win32_Window>(title, width, height, pixelSize, fullscreen);
#endif
        AIO_ASSERT(false, "API has not been selected.\n");
        return nullptr;
    }
}