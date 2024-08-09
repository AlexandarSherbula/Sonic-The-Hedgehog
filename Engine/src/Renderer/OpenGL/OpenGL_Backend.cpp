#include "aio_pch.h"

#if defined(AIO_API_OPENGL)
#include "OpenGL_Backend.h"
#include "OpenGL_Buffer.h"
#include "OpenGL_Shader.h"
#include "Window/GLFW_Window.h"

#include "Alexio/Engine.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Alexio
{
	OpenGL_Backend* OpenGL_Backend::sInstance = nullptr;

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AIO_LOG_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AIO_LOG_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AIO_LOG_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AIO_LOG_TRACE(message); return;
		}

		AIO_ASSERT(false, "Unknown severity level!");
	}


	OpenGL_Backend::OpenGL_Backend()
	{
		AIO_ASSERT(!sInstance, "OpenGL backend has already been made");
		sInstance = this;
	}

	OpenGL_Backend::~OpenGL_Backend()
	{
		glfwTerminate();
	}

	void OpenGL_Backend::Initialize()
	{
		int gladLoad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AIO_ASSERT(gladLoad, "Failed to initialize GLAD");

#ifdef AIO_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif		
		AIO_LOG_INFO("OpenGL ({0}) Initialized", (const char*)glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGL_Backend::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGL_Backend::Draw(uint32_t vertexCount)
	{
		// Currently not in function. To be reworked
		/*
		GLenum mode = GL_TRIANGLES;

		switch (vertexCount)
		{
		case 0: AIO_LOG_ERROR("No vertices found"); break;
		case 1: mode = GL_POINT; break;
		case 2: mode = GL_LINES; break;
		}
		*/

		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void OpenGL_Backend::DrawIndexed(uint32_t indexCount)
	{		
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void OpenGL_Backend::Clear(float r, float g, float b, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void OpenGL_Backend::SwapBuffer()
	{
		glfwSwapInterval((int)mVSync);
		glfwSwapBuffers((GLFWwindow*)Engine::GetInstance()->GetWindow()->GetHandle());
	}

	void OpenGL_Backend::ImGuiBackendInit()
	{
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::GetInstance()->GetWindow()->GetHandle(), true);
		ImGui_ImplOpenGL3_Init("#version 450 core");
	}

	void OpenGL_Backend::ImGuiBackendBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGL_Backend::ImGuiBackendUpdate()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void OpenGL_Backend::ImGuiBackendShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}
}
#endif

