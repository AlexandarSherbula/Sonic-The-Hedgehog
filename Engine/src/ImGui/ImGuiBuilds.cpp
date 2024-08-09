#include "aio_pch.h"

#if defined(AIO_API_OPENGL)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.cpp>
#include <backends/imgui_impl_opengl3.cpp>
#endif

#if defined (AIO_PLATFORM_WINDOWS) && defined(AIO_API_DX11)
#include <backends/imgui_impl_win32.cpp>
#include <backends/imgui_impl_dx11.cpp>
#endif // AIO_PLATFORM_WINDOWS
