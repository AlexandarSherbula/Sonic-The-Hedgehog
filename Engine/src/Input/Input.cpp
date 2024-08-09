#include "aio_pch.h"
#include "Input.h"
#include "Gamepad.h"

#include "Renderer/Renderer.h"

namespace Alexio
{
	std::array<bool, 256> Input::oldKeyState = { false };
	std::array<bool, 256> Input::newKeyState = { false };
	std::array<States, 256> Input::keyStates = { false };

	std::array<bool, 8> Input::oldMouseButtonState = { false };
	std::array<bool, 8> Input::newMouseButtonState = { false };
	std::array<States, 8> Input::mouseButtonStates = { false };

	std::unordered_map<size_t, int8_t> Input::mapKeys;

	void Input::Poll()
	{
		for (int i = 0; i < keyStates.size(); i++)
			Scan(keyStates[i], oldKeyState[i], newKeyState[i]);

		for (int i = 0; i < mouseButtonStates.size(); i++)
			Scan(mouseButtonStates[i], oldMouseButtonState[i], newMouseButtonState[i]);

		Gamepad::PollEvents();
	}

	void Input::Scan(States& state, bool& oldState, bool& newState)
	{
		state.pressed = false;
		state.released = false;

		if (newState != oldState)
		{
			if (newState)
			{
				state.pressed = !state.held;
				state.held = true;
			}
			else
			{
				state.released = true;
				state.held = false;
			}
		}

		oldState = newState;
	}

	void Input::UpdateKeyState(int32_t keycode, bool state)
	{
		newKeyState[keycode] = state;
	}

	void Input::UpdateMouseState(int32_t mousebutton, bool state)
	{
		newMouseButtonState[mousebutton] = state;
	}

	void Input::Init()
	{
		Gamepad::Init();
	}

	void Input::SetKeyCodes()
	{
		mapKeys[0x41] = Key::A; mapKeys[0x42] = Key::B; mapKeys[0x43] = Key::C; mapKeys[0x44] = Key::D; mapKeys[0x45] = Key::E;
		mapKeys[0x46] = Key::F; mapKeys[0x47] = Key::G; mapKeys[0x48] = Key::H; mapKeys[0x49] = Key::I; mapKeys[0x4A] = Key::J;
		mapKeys[0x4B] = Key::K; mapKeys[0x4C] = Key::L; mapKeys[0x4D] = Key::M; mapKeys[0x4E] = Key::N; mapKeys[0x4F] = Key::O;
		mapKeys[0x50] = Key::P; mapKeys[0x51] = Key::Q; mapKeys[0x52] = Key::R; mapKeys[0x53] = Key::S; mapKeys[0x54] = Key::T;
		mapKeys[0x55] = Key::U; mapKeys[0x56] = Key::V; mapKeys[0x57] = Key::W; mapKeys[0x58] = Key::X; mapKeys[0x59] = Key::Y;
		mapKeys[0x5A] = Key::Z;

#if defined(AIO_API_OPENGL) && defined(AIO_API_DX11)
        if (Renderer::GetGraphicsAPI() == OpenGL)
            SetGLFWKeyCodes(mapKeys);
        else if (Renderer::GetGraphicsAPI() == DirectX11)
            SetWin32KeyCodes(mapKeys);
#elif defined(AIO_API_OPENGL)
        SetGLFWKeyCodes(mapKeys);
#elif defined(AIO_API_DX11)
        SetWin32KeyCodes(mapKeys);
#endif
	}
}