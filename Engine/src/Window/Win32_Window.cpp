#include "aio_pch.h"

#if defined(AIO_API_DX11)
#include "Win32_Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/DX11/DX11_Backend.h"

#include <imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Alexio
{
	static EventCallbackFn ecFn;

	Win32_Window::Win32_Window(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen)
	{
		mProjectionWidth = width;
		mProjectionHeight = height;
		mTitle = title;

		mPixelSize = pixelSize;

		mWindowClass = L"Win32 Class";
		m_hInstance = GetModuleHandle(nullptr);

		mIsFullScreen = fullscreen;
		mFullScreen = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

		mWindowRect = {};
	}

	Win32_Window::~Win32_Window()
	{
		DestroyWindow(mHandle);
		UnregisterClass(mWindowClass, m_hInstance);
	}

	void Win32_Window::Initialize()
	{
		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = NULL;
		wc.hIconSm = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = mWindowClass;
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);

		mWindowSize.x = mProjectionWidth * mPixelSize;
		mWindowSize.y = mProjectionHeight * mPixelSize;

		mPosition = { mFullScreen.x / 2.0f - mWindowSize.x / 2.0f, mFullScreen.y / 2.0f - mWindowSize.y / 2.0f };
		
		mWindowRect.left = mPosition.x;
		mWindowRect.top = mPosition.y;
		mWindowRect.right = mWindowRect.left + mWindowSize.x;
		mWindowRect.bottom = mWindowRect.top + mWindowSize.y;

		DWORD style = mIsFullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;

		if (mIsFullScreen)
		{
			MONITORINFO mi = { sizeof(mi) };
			HMONITOR hmon = MonitorFromWindow(mHandle, MONITOR_DEFAULTTONEAREST);
			if (GetMonitorInfo(hmon, &mi))
			{
				RECT fullscreenRect = { mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom };

				if (!AdjustWindowRect(&fullscreenRect, style, FALSE))
					std::cout << "Failed to adjust window" << std::endl;

				mHandle = CreateWindowEx(0, mWindowClass, StringToWide(mTitle).c_str(), style,
					fullscreenRect.left, fullscreenRect.top, fullscreenRect.right - fullscreenRect.left, fullscreenRect.bottom - fullscreenRect.top,
					NULL, NULL, m_hInstance, NULL);

				mWindowSize = mFullScreen;
			}
		}
		else
		{
			if (!AdjustWindowRect(&mWindowRect, style, FALSE))
				std::cout << "Failed to adjust window" << std::endl;

			mHandle = CreateWindowEx(0, mWindowClass, StringToWide(mTitle).c_str(), style,
				mWindowRect.left, mWindowRect.top, mWindowRect.right - mWindowRect.left, mWindowRect.bottom - mWindowRect.top,
				NULL, NULL, m_hInstance, NULL);
		}

		AIO_ASSERT(mHandle, "Failed to create a Window: " + ResultInfo(GetLastError()));

		ShowWindow(mHandle, SW_SHOWDEFAULT);
		SetForegroundWindow(mHandle);
		SetFocus(mHandle);
	}

	void Win32_Window::SetEventCallback(const EventCallbackFn& callback)
	{		
		ecFn = callback;
		Initialize();
	}

	void Win32_Window::PixelResize(uint32_t pixelSize)
	{
		if (!mIsFullScreen)
		{
			mPixelSize = pixelSize;

			mWindowSize.x = mProjectionWidth * mPixelSize;
			mWindowSize.y = mProjectionHeight * mPixelSize;

			static RECT windowRect = {};

			mPosition = { mFullScreen.x / 2.0f - mWindowSize.x / 2.0f, mFullScreen.y / 2.0f - mWindowSize.y / 2.0f };

			mWindowRect.left = mPosition.x;
			mWindowRect.top = mPosition.y;
			mWindowRect.right = mWindowRect.left + mWindowSize.x;
			mWindowRect.bottom = mWindowRect.top + mWindowSize.y;

			SetWindowPos(mHandle, NULL,
				mWindowRect.left, mWindowRect.top, mWindowRect.right - mWindowRect.left, mWindowRect.bottom - mWindowRect.top,
				SWP_SHOWWINDOW);
		}
	}

	void Win32_Window::SetFullScreen()
	{
		mIsFullScreen = !mIsFullScreen;

		static RECT windowRect = {};

		DWORD style = mIsFullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
		SetWindowLong(mHandle, GWL_STYLE, style);

		if (mIsFullScreen)
		{			
			MONITORINFO mi = { sizeof(mi) };
			if (GetMonitorInfo(MonitorFromWindow(mHandle,
				MONITOR_DEFAULTTONEAREST), &mi))
			{
				SetWindowPos(mHandle, HWND_TOP,
					mi.rcMonitor.left, mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_SHOWWINDOW);

				mWindowSize = mFullScreen;
			}
		}
		else
		{
			SetWindowPos(mHandle, NULL,
				mWindowRect.left, mWindowRect.top, mWindowRect.right - mWindowRect.left, mWindowRect.bottom - mWindowRect.top,
				SWP_SHOWWINDOW);

			mWindowSize.x = mProjectionWidth * mPixelSize;
			mWindowSize.y = mProjectionHeight * mPixelSize;
		}
	}

	void Win32_Window::PollEvents()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}		
	}

	LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
			return true;

		// WINDOW EVENTS
		switch (uMsg)
		{
		case WM_SIZE:
		{			
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			WindowResizeEvent event(width, height);
			ecFn(event);
			return 0;
		}
		case WM_CLOSE:
		{
			WindowCloseEvent event;
			ecFn(event);
			return 0;
		}


		// KEY EVENTS
		case WM_SYSKEYDOWN:
		{
			int32_t keycode;
			int32_t isRight = (lParam >> 24) & 0x01;

			switch (wParam)
			{
			case 18: keycode = (isRight) ? Key::R_ALT : Key::L_ALT; break;
			case 121: keycode = Key::F10; break;
			default:
				keycode = Input::mapKeys[wParam];
			}
			KeyPressedEvent event(keycode, LOWORD(lParam));
			ecFn(event);
			Input::UpdateKeyState(keycode, true);
			return 0;
		}
		case WM_SYSKEYUP:
		{
			int32_t keycode;
			int32_t isRight = (lParam >> 24) & 0x01;

			switch (wParam)
			{
			case 18: keycode = (isRight) ? Key::R_ALT : Key::L_ALT; break;
			case 121: keycode = Key::F10; break;
			default:
				keycode = Input::mapKeys[wParam];
			}
			KeyPressedEvent event(wParam, LOWORD(lParam));
			ecFn(event);
			Input::UpdateKeyState(keycode, false);
			return 0;
		}
		case WM_KEYDOWN:
		{
			KeyPressedEvent event(wParam, LOWORD(lParam));
			ecFn(event);

			int32_t keycode;
			bool isRight;

			switch (wParam)
			{
			case 16:
			{
				isRight = (lParam >> 20) & 0x01;
				keycode = (isRight) ? Key::R_SHIFT : Key::L_SHIFT; break;
			}
			case 17:
			{
				isRight = (lParam >> 24) & 0x01;
				keycode = (isRight) ? Key::R_CTRL : Key::L_CTRL; break;
			}
			default:
				keycode = Input::mapKeys[wParam];
			}
			Input::UpdateKeyState(keycode, true);
			return 0;
		}
		case WM_KEYUP:
		{
			KeyReleasedEvent event(wParam);
			ecFn(event);

			int32_t keycode;
			int32_t isRight;

			switch (wParam)
			{
			case 16:
			{
				isRight = (lParam >> 20) & 0x01;
				keycode = (isRight) ? Key::R_SHIFT : Key::L_SHIFT; break;
			}
			case 17:
			{
				isRight = (lParam >> 24) & 0x01;
				keycode = (isRight) ? Key::R_CTRL : Key::L_CTRL; break;
			}
			default:
				keycode = Input::mapKeys[wParam];
			}
			Input::UpdateKeyState(keycode, false);
			return 0;
		}

		// MOUSE PRESS EVENTS
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressedEvent event(MK_LBUTTON);
			ecFn(event);
			Input::UpdateMouseState(L_BUTTON, true);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent event(MK_RBUTTON);
			ecFn(event);
			Input::UpdateMouseState(R_BUTTON, true);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressedEvent event(MK_MBUTTON);
			ecFn(event);
			Input::UpdateMouseState(M_BUTTON, true);
			return 0;
		}
		case WM_XBUTTONDOWN:
		{
			int mouseButton = (wParam & MK_XBUTTON1) | (wParam & MK_XBUTTON2);
			MouseButtonPressedEvent event(mouseButton);
			ecFn(event);
			if (mouseButton == 32)
				mouseButton = X_BUTTON1;
			else if (mouseButton == 64)
				mouseButton = X_BUTTON2;
			Input::UpdateMouseState(mouseButton, true);
			return 0;
		}

		// MOUSE RELEASE EVENTS
		case WM_LBUTTONUP:
		{
			MouseButtonReleasedEvent event(MK_LBUTTON);
			ecFn(event);
			Input::UpdateMouseState(L_BUTTON, false);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent event(MK_RBUTTON);
			ecFn(event);
			Input::UpdateMouseState(R_BUTTON, false);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleasedEvent event(MK_MBUTTON);
			ecFn(event);
			Input::UpdateMouseState(M_BUTTON, false);
			return 0;
		}
		case WM_XBUTTONUP:
		{
			UINT xbuttoncode = wParam;
			if (wParam == 131072)		xbuttoncode = (wParam | 0x0040) & 0x0040;
			else if (wParam == 65536)	xbuttoncode = (wParam | 0x0020) & 0x0020;
			MouseButtonReleasedEvent event(xbuttoncode);
			ecFn(event);
			if (xbuttoncode == 32)
				xbuttoncode = X_BUTTON1;
			else if (xbuttoncode == 64)
				xbuttoncode = X_BUTTON2;
			Input::UpdateMouseState(xbuttoncode, false);
			return 0;
		}

		// MOUSE SCROLL EVENTS
		case WM_MOUSEWHEEL:
		{
			// I have no mouse to test the x-axis scrolling so for now it's set to 0.
			MouseScrolledEvent event(0, GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
			ecFn(event);
			return 0;
		}

		// MOUSE MOVE EVENTS
		case WM_MOUSEMOVE:
		{
			MouseMovedEvent event((float)LOWORD(lParam), (float)HIWORD(lParam));
			ecFn(event);
			return 0;
		}

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		};
	}

	std::string ResultInfo(HRESULT hr)
	{
		_com_error error(hr);
		return WideToString(error.ErrorMessage());
	}
}
#endif