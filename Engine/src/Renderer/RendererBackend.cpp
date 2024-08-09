#include "aio_pch.h"

#include "OpenGL/OpenGL_Backend.h"
#include "DX11/DX11_Backend.h"

#include "Alexio/Utilities.h"

namespace Alexio
{
    GraphicsAPI RendererBackend::sAPI = Null;

    Ref<RendererBackend> RendererBackend::Create()
    {
        #if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
            switch (sAPI)
            {
            case OpenGL:    return CreateRef<OpenGL_Backend>();
            case DirectX11: return CreateRef<DX11_Backend>();
            }
        #elif defined(AIO_API_OPENGL)
            return CreateRef<OpenGL_Backend>();
        #elif defined(AIO_API_DX11)
             return CreateRef<DX11_Backend>();
        #endif
        AIO_ASSERT(false, "API has not been selected.\n");
        sAPI = GraphicsAPI::Null;
        return nullptr;
    }
}