#pragma once

#include "Alexio/Utilities.h"
#include "Events/Events.h"
#include "Input/Input.h"
#include "Math/Math.h"

#include <functional>

namespace Alexio
{
	using EventCallbackFn = std::function<void(Event&)>;

	class Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Initialize() = 0;

		virtual void PollEvents() = 0;

		inline uint32_t GetProjectionWidth()  const { return mProjectionWidth; }
		inline uint32_t GetProjectionHeight() const { return mProjectionHeight; }

		inline uint32_t GetPixelSize() const { return mPixelSize; }
		inline Alexio::Vector2 GetWindowSize() const { return mWindowSize; }
		inline bool IsFullScreen() const { return mIsFullScreen; }
		inline virtual Alexio::Vector2 GetFullScreen() const { return mFullScreen; }

		virtual void* GetHandle() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void PixelResize(uint32_t pixelSize) = 0;
		virtual void SetFullScreen() = 0;
	
		static Ref<Window> Create(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen);
	protected:
		Alexio::Vector2 mPosition;
		Alexio::Vector2 mWindowSize;
		uint32_t mPixelSize;
		uint32_t mProjectionWidth;
		uint32_t mProjectionHeight;
		std::string mTitle;

		bool mIsFullScreen;
		Alexio::Vector2 mFullScreen;
	};

}