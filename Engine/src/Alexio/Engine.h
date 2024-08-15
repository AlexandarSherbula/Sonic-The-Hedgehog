#pragma once

#include "Layer.h"
#include "Log.h"
#include "Timer.h"
#include "Utilities.h"
#include "Random.h"

#include "Math/Math.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "ImGui/ImGuiLayer.h"

#define AIO_ENGINE Alexio::Engine::GetInstance()
#define AIO_WINDOW Alexio::Engine::GetInstance()->GetWindow()

namespace Alexio
{
	class Engine
	{
	public:
		inline static Engine* GetInstance() { return sInstance; }
	public:
		Engine();
		void Run(const std::string& title = "Alexio Engine", uint32_t projection_width = 1280, uint32_t projection_height = 720, uint32_t pixelSize = 1, bool fullscreen = false);

		void OnEvent(Event& e);

		virtual bool OnStart() = 0;
		virtual bool OnUpdate() = 0;
		virtual bool OnFixedUpdate() = 0;
		virtual bool OnLateUpdate() = 0;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window* GetWindow() const { return mWindow.get(); }
		inline static Camera* GetCamera() { return sMainCamera.get(); }

		inline void SetFullScreen() { mWindow->SetFullScreen(); }
		inline bool IsFullScreen() const { return mWindow->IsFullScreen(); }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<Window> mWindow;
		bool mRunning;
		double mPhysicsSimulated;
		
		LayerStack mLayerStack;
		ImGUI imgui;
	private:
		static Engine* sInstance;
		static Ref<Camera> sMainCamera;
	};
}