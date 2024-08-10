#pragma once

#include "Math/Math.h"
#include "KeyCodes.h"

#include "SDL.h"

namespace Alexio
{	
	class Gamepad
	{
	private:
		static SDL_GameController* sController;
		static std::string sName;
	
		static std::array<States, 23> sButtonStates;
		static std::array<bool, 23>   sNewButtonStates;
		static std::array<bool, 23>   sOldButtonStates;
	
		static Vector2 sLeftThumbStick;
		static Vector2 sRightThumbStick;
	
		static float sLeftTrigger;
		static float sRightTrigger;
	
		static float sDeadZone;
	public:	
		static void Init();
		static inline bool IsConnected() { return sController == nullptr; }
		static inline void UpdateButtonState(int32_t buttoncode, bool state) { sNewButtonStates[buttoncode] = state; }

		static inline bool ButtonPressed(int32_t buttoncode) { return sButtonStates[buttoncode].pressed; }
		static inline bool ButtonHeld(int32_t buttoncode) { return sButtonStates[buttoncode].held; }
		static inline bool ButtonReleased(int32_t buttoncode) { return sButtonStates[buttoncode].released; }
	
		static inline float DeadZone() { return sDeadZone; }
	
		static inline Vector2 LeftThumbStick() { return sLeftThumbStick; }
		static inline Vector2 RightThumbStick() { return sRightThumbStick; }

		static inline bool L_ThumbStickHeldLeft() { return sButtonStates[15].held; }
		static inline bool L_ThumbStickReleasedLeft() { return sButtonStates[15].released; }

		static inline bool L_ThumbStickHeldRight() { return sButtonStates[16].held; }
		static inline bool L_ThumbStickReleasedRight() { return sButtonStates[16].released; }

		static inline bool L_ThumbStickHeldUp() { return sButtonStates[17].held; }
		static inline bool L_ThumbStickReleasedUp() { return sButtonStates[17].released; }

		static inline bool L_ThumbStickHeldDown() { return sButtonStates[18].held; }
		static inline bool L_ThumbStickReleasedDown() { return sButtonStates[18].released; }

		static inline bool R_ThumbStickHeldLeft() { return sButtonStates[19].held; }
		static inline bool R_ThumbStickReleasedLeft() { return sButtonStates[19].released; }

		static inline bool R_ThumbStickHeldRight() { return sButtonStates[20].held; }
		static inline bool R_ThumbStickReleasedRight() { return sButtonStates[20].released; }

		static inline bool R_ThumbStickHeldUp() { return sButtonStates[21].held; }
		static inline bool R_ThumbStickReleasedUp() { return sButtonStates[21].released; }

		static inline bool R_ThumbStickHeldDown() { return sButtonStates[22].held; }
		static inline bool R_ThumbStickReleasedDown() { return sButtonStates[22].released; }
	
		static inline float LeftTrigger() { return sLeftTrigger; }
		static inline float RightTrigger() { return sRightTrigger; }
	
		static void SetDeadZone(float deadZone);
		static void PollEvents();

		static void Close();
	};
}

