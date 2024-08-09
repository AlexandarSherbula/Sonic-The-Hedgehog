#pragma once

#include "Window/Window.h"

#if defined(AIO_API_DX11)
namespace Alexio
{
	class Win32_Window : public Window
	{
	public:
		Win32_Window(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen);
		~Win32_Window();
		void Initialize() override;
		void PollEvents() override;

		inline void* GetHandle() const override { return mHandle; }
		void SetEventCallback(const EventCallbackFn& callback) override;
		void PixelResize(uint32_t pixelSize) override;
		void SetFullScreen() override;
	private:
		HWND mHandle = nullptr;
		HINSTANCE m_hInstance;
		const WCHAR* mWindowClass;
		RECT mWindowRect;
	};
	
	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::string ResultInfo(HRESULT hr);
}
#endif