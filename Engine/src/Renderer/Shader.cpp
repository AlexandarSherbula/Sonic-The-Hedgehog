#include "aio_pch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/OpenGL_Shader.h"
#include "Renderer/DX11/DX11_Shader.h"

namespace Alexio
{
    Ref<Shader> Shader::Create(const std::string& name, const Ref<VertexArray>& vertexArray)
    {
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (Renderer::GetGraphicsAPI())
            {
            case OpenGL:    return CreateRef<OpenGL_Shader>(name, vertexArray);
            case DirectX11: return CreateRef<DX11_Shader>(name, vertexArray);
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Shader>(name, vertexArray);
        #elif defined(AIO_API_DX11)
            return CreateRef<DX11_Shader>(name, vertexArray);
        #endif
            AIO_ASSERT(false, "API has not been selected.\n");
            return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath, const Ref<VertexArray>& vertexArray)
	{
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (Renderer::GetGraphicsAPI())
            {
            case OpenGL:    return CreateRef<OpenGL_Shader>(name, filepath, vertexArray);
            case DirectX11: return CreateRef<DX11_Shader>(name, filepath, vertexArray);
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Shader>(name, filepath, vertexArray);
        #elif defined(AIO_API_DX11)
            return CreateRef<DX11_Shader>(name, filepath, vertexArray);
        #endif
            AIO_ASSERT(false, "API has not been selected.\n");
            return nullptr;
	}

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexArray>& vertexArray)
    {
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (Renderer::GetGraphicsAPI())
            {
            case OpenGL:    return CreateRef<OpenGL_Shader>(name, vertexSrc, pixelSrc, vertexArray);
            case DirectX11: return CreateRef<DX11_Shader>(name, vertexSrc, pixelSrc, vertexArray);
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Shader>(name, vertexSrc, pixelSrc, vertexArray);
        #elif defined(AIO_API_DX11)
            return CreateRef<DX11_Shader>(name, vertexSrc, pixelSrc, vertexArray);
        #endif
            AIO_ASSERT(false, "API has not been selected.\n");
            return nullptr;
    }
}


