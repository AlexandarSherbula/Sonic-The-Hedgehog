#pragma once

#include "Window/Window.h"

#if defined(AIO_API_OPENGL)
namespace Alexio
{
	class GLFW_Window : public Window
	{
	public:
		GLFW_Window(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen);
		~GLFW_Window();
		void Initialize();
		void PollEvents() override;

		inline void* GetHandle() const override { return mHandle; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { mData.eventCallback = callback; }
		void PixelResize(uint32_t pixelSize) override;
		void SetFullScreen() override;
	private:
		void EventProcess();
	private:
		GLFWwindow* mHandle;
		GLFWmonitor* mMonitor;

		struct WindowDataFromCallback
		{
			std::string title;
			uint32_t width, height;

			EventCallbackFn eventCallback;
		};

		WindowDataFromCallback mData;
	};
}
#endif