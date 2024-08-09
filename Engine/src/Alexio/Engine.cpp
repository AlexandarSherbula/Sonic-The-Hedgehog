#include "aio_pch.h"
#include "Engine.h"

namespace Alexio
{
	Engine* Engine::sInstance = nullptr;
	Ref<Camera> Engine::sMainCamera = nullptr;

	Engine::Engine()
	{
		Alexio::Log::Initialize();

		AIO_ASSERT(!sInstance, "An instance of Engine has already been made");
		sInstance = this;

		mPhysicsSimulated = 0.0;

		Renderer::SetGraphicsAPI(DirectX11);
		imgui = ImGUI();
		mRunning = true;
	}

	void Engine::Run(const std::string& title, uint32_t projection_width, uint32_t projection_height, uint32_t pixelSize, bool fullscreen)
	{
		mWindow = Window::Create(title, projection_width, projection_height, pixelSize, fullscreen);
		mWindow->SetEventCallback(AIO_BIND_EVENT_FN(Engine::OnEvent));

		Input::Init();
		Input::SetKeyCodes();

		sMainCamera = CreateRef<Camera>(Alexio::Vector2(projection_width, projection_height));
		Renderer::Init();
		Renderer::SetViewport(0, 0, mWindow->GetWindowSize().x, mWindow->GetWindowSize().y);
		Random::Init();

		AIO_ASSERT(OnStart(), "Failed to initialize application");

		PushOverlay(&imgui);

		Timer::StartApp();
		while (mRunning)
		{
			Timer::Update();

			mWindow->PollEvents();
			Input::Poll();

			Renderer::Stats = {0};
			
			imgui.Begin();

			while (mPhysicsSimulated < Timer::Get())
			{
				OnFixedUpdate();
				mPhysicsSimulated += 1.0f / 60.0f;
			}

			if (!OnUpdate() ||
				// Manual code for closing on alt + F4 for Win32 API, since the system keys are not being checked
				(Renderer::GetGraphicsAPI() == DirectX11 && (Input::KeyHeld(L_ALT) && Input::KeyPressed(F4))))
				mRunning = false;

			sMainCamera->OnUpdate(Timer::DetlaTime());
			Renderer::Flush();
			imgui.End();

			Renderer::GetBackend()->SwapBuffer();

			Timer::EndFrame();
		}

		Gamepad::Close();
		imgui.OnDetach();
		Renderer::End();
	}

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AIO_BIND_EVENT_FN(Engine::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(AIO_BIND_EVENT_FN(Engine::OnWindowResize));

		if (sMainCamera != nullptr)
			sMainCamera->OnEvent(e);

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Engine::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}

	void Engine::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	bool Engine::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}
}



