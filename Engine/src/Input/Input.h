#pragma once

#include "Input/KeyCodes.h"
#include "Math/Math.h"

#include "Gamepad.h"

namespace Alexio
{
	class Gamepad;

	class Input
	{
	private:
		static std::array<States, 256> keyStates;
		static std::array<bool, 256> newKeyState;
		static std::array<bool, 256> oldKeyState;

		static std::array<States, 8> mouseButtonStates;
		static std::array<bool, 8> newMouseButtonState;
		static std::array<bool, 8> oldMouseButtonState;

	public:
		static std::unordered_map<size_t, int8_t> mapKeys;
	public:
		static void Init();
		static void SetKeyCodes();
		static void Poll();
		static void Scan(States& state, bool& oldState, bool& newState);
		static void UpdateKeyState(int32_t keycode, bool state);
		static void UpdateMouseState(int32_t mousebutton, bool state);

		inline static States GetKeyState(int keycode) { return keyStates[keycode]; }

		static inline bool KeyPressed(int32_t keycode) { return keyStates[keycode].pressed; }
		static inline bool KeyHeld(int32_t keycode) { return keyStates[keycode].held; }
		static inline bool KeyReleased(int32_t keycode) { return keyStates[keycode].released; }

		static inline bool MouseButtonPressed(int32_t mb) { return mouseButtonStates[mb].pressed; }
		static inline bool MouseButtonHeld(int32_t mb) { return mouseButtonStates[mb].held; }
		static inline bool MouseButtonReleased(int32_t mb) { return mouseButtonStates[mb].released; }


	};	
}

