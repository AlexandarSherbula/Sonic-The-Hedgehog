#include "aio_pch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/OpenGL_Texture.h"
#include "Renderer/DX11/DX11_Texture.h"

namespace Alexio
{
    Ref<Texture> Texture::Create(uint32_t width, uint32_t height, uint32_t whiteTexture)
    {
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (Renderer::GetGraphicsAPI())
            {
            case OpenGL:    return CreateRef<OpenGL_Texture>(width, height, whiteTexture);
            case DirectX11: return CreateRef<DX11_Texture>(width, height, whiteTexture);
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Texture>(width, height, whiteTexture);
        #elif defined(AIO_API_DX11)
            return CreateRef<DX11_Texture>(width, height, whiteTexture);
        #endif
        AIO_ASSERT(false, "API has not been selected.\n");
        return nullptr;
    }

    Ref<Texture> Texture::Create(const std::string& filepath)
    {
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (Renderer::GetGraphicsAPI())
            {
            case OpenGL:    return CreateRef<OpenGL_Texture>(filepath);
            case DirectX11: return CreateRef<DX11_Texture>(filepath);
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Texture>(filepath);
        #elif defined(AIO_API_DX11)
            return CreateRef<DX11_Texture>(filepath);
        #endif
        AIO_ASSERT(false, "API has not been selected.\n");
        return nullptr;
    }
}