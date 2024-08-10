#pragma once

#include "Alexio/Engine.h"

#include "Act.h"
#include "Objects/Player.h"
#include "CameraController.h"

class Game : public Alexio::Engine
{
public:
	Act currentAct;
	Player player;
	CameraController cameraController;
public:
	Game();

	bool OnStart() override;
	bool OnUpdate() override;
	bool OnFixedUpdate() override;
	
	void OnImGuiRender();

	inline bool UpButtonHeld() { return Alexio::Input::KeyHeld(UP) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_UP) || Alexio::Gamepad::L_ThumbStickHeldUp(); }
	inline bool UpButtonReleased() { return Alexio::Input::KeyReleased(UP) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_UP) || Alexio::Gamepad::L_ThumbStickReleasedUp(); }

	inline bool DownButtonHeld() { return Alexio::Input::KeyHeld(DOWN) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_DOWN) || Alexio::Gamepad::L_ThumbStickHeldDown(); }
	inline bool DownButtonReleased() { return Alexio::Input::KeyReleased(DOWN) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_DOWN) || Alexio::Gamepad::L_ThumbStickReleasedDown(); }

	inline bool LeftButtonHeld() { return Alexio::Input::KeyHeld(LEFT) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_LEFT) || Alexio::Gamepad::L_ThumbStickHeldLeft(); }
	inline bool LeftButtonReleased() { return Alexio::Input::KeyReleased(LEFT) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_LEFT) || Alexio::Gamepad::L_ThumbStickReleasedLeft(); }

	inline bool RightButtonHeld() { return Alexio::Input::KeyHeld(RIGHT) || Alexio::Gamepad::ButtonHeld(Xbox::D_PAD_RIGHT) || Alexio::Gamepad::L_ThumbStickHeldRight(); }
	inline bool RightButtonReleased() { return Alexio::Input::KeyReleased(RIGHT) || Alexio::Gamepad::ButtonReleased(Xbox::D_PAD_RIGHT) || Alexio::Gamepad::L_ThumbStickReleasedRight(); }

	inline bool JumpButtonHeld() {
		return Alexio::Input::KeyHeld(A) || Alexio::Input::KeyHeld(S) || Alexio::Input::KeyHeld(D) ||
			Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_A) || Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_B) || Alexio::Gamepad::ButtonHeld(Xbox::BUTTON_X);
	}

	inline bool JumpButtonReleased() {
		return Alexio::Input::KeyReleased(A) || Alexio::Input::KeyReleased(S) || Alexio::Input::KeyReleased(D) ||
			Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_A) || Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_B) || Alexio::Gamepad::ButtonReleased(Xbox::BUTTON_X);
	}
};

inline Game game;