#include "aio_pch.h"
#include "Input.h"
#include "Gamepad.h"

namespace Alexio
{	
	std::array<States, 23> Gamepad::sButtonStates = { false };
	std::array<bool, 23>   Gamepad::sNewButtonStates = { false };
	std::array<bool, 23>   Gamepad::sOldButtonStates = { false };

	Vector2 Gamepad::sLeftThumbStick = { 0.0f, 0.0f };
	Vector2 Gamepad::sRightThumbStick = { 0.0f, 0.0f };

	float Gamepad::sDeadZone = 0.3f;
	float Gamepad::sLeftTrigger = 0.0f;
	float Gamepad::sRightTrigger = 0.0f;

	SDL_GameController* Gamepad::sController = nullptr;
	std::string Gamepad::sName = "";
	
	void Gamepad::Init()
	{
		AIO_ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == 0, "Failed to initialize SDL" + std::string(SDL_GetError()));

		if (SDL_IsGameController(0))
		{
			sController = SDL_GameControllerOpen(0);
			if (!sController)
			{
				AIO_LOG_ERROR("Failed to open the controller");
			}
		}
	}
	
	void Gamepad::SetDeadZone(float deadZone)
	{
		if (deadZone > 0.0f && deadZone < 1.0f) 
			sDeadZone = deadZone;
		else if (deadZone < 0.0f)
			sDeadZone = 0.0f;
		else
			sDeadZone = 1.0f;
	}
	
	void Gamepad::PollEvents()
	{
		SDL_Event sdl_event;
		// Check for available controllers
		int numJoysticks = SDL_NumJoysticks();

		// Open the first available controller
		sController = nullptr;
		for (int i = 0; i < numJoysticks; i++)
		{
			if (SDL_IsGameController(i))
			{
				sController = SDL_GameControllerOpen(i);
				std::string gameControllerName = SDL_GameControllerName(sController);
				if (gameControllerName.find("Controller") == std::string::npos && gameControllerName.find("Gamepad") == std::string::npos)
				{
					sController = nullptr;
					numJoysticks--;
					continue;
				}
				if (sController)
				{
					SDL_GameControllerType type = SDL_GameControllerGetType(sController);
					switch (type) {
					case SDL_CONTROLLER_TYPE_XBOX360:
						sName = "Xbox360";
						break;
					case SDL_CONTROLLER_TYPE_XBOXONE:
						sName = "XboxOne";
						break;
					case SDL_CONTROLLER_TYPE_PS3:
						sName = "DualShock3";
						break;
					case SDL_CONTROLLER_TYPE_PS4:
						sName = "DualShock4";
						break;
					case SDL_CONTROLLER_TYPE_PS5:
						sName = "DualSense";
						break;
					case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO:
						sName = "NintendoSwitchPro";
						break;
					case SDL_CONTROLLER_TYPE_UNKNOWN:
						sName = "Unknown";
						break;
					default:
						AIO_LOG_ERROR("Controller is unsupported");
						break;
					}
				}
			}

			//sLeftThumbStick = { 0.0f, 0.0f };
			//sRightThumbStick = { 0.0f, 0.0f };
			//sLeftTrigger = 0.0f;
			//sRightTrigger = 0.0f;


			while (SDL_PollEvent(&sdl_event))
			{
				switch (sdl_event.type)
				{
					case SDL_CONTROLLERBUTTONDOWN:
					{
						if (sdl_event.cbutton.button <= 14)
							UpdateButtonState(sdl_event.cbutton.button, true);
						break;
					}
					case SDL_CONTROLLERBUTTONUP:
					{
						if (sdl_event.cbutton.button <= 14)
							UpdateButtonState(sdl_event.cbutton.button, false);
						break;
					}
					case SDL_CONTROLLERAXISMOTION:
					{
						switch (sdl_event.caxis.axis)
						{
							case SDL_CONTROLLER_AXIS_LEFTX:
							{
								sLeftThumbStick.x = sdl_event.caxis.value / 32767.0f;

								if (sLeftThumbStick.x < -sDeadZone)
									UpdateButtonState(15, true);
								else if (sLeftThumbStick.x >= -sDeadZone && sLeftThumbStick.x <= 0.0f && sOldButtonStates[15])
									UpdateButtonState(15, false);

								if (sLeftThumbStick.x > sDeadZone)
									UpdateButtonState(16, true);
								else if (sLeftThumbStick.x >= 0.0f && sLeftThumbStick.x <= sDeadZone && sOldButtonStates[16])
									UpdateButtonState(16, false);

								break;
							}
							case SDL_CONTROLLER_AXIS_LEFTY:
							{
								if (sLeftThumbStick.y < -sDeadZone)
									UpdateButtonState(17, true);
								else if (sLeftThumbStick.y >= -sDeadZone && sLeftThumbStick.y <= 0.0f && sOldButtonStates[17])
									UpdateButtonState(17, false);

								if (sLeftThumbStick.y > sDeadZone)
									UpdateButtonState(18, true);
								else if (sLeftThumbStick.y >= 0.0f && sLeftThumbStick.y <= sDeadZone && sOldButtonStates[18])
									UpdateButtonState(18, false);

								sLeftThumbStick.y = sdl_event.caxis.value / 32767.0f;
								break;
							}
							case SDL_CONTROLLER_AXIS_RIGHTX:
							{
								sRightThumbStick.x = sdl_event.caxis.value / 32767.0f;

								if (sRightThumbStick.x < -sDeadZone)
									UpdateButtonState(19, true);
								else if (sRightThumbStick.x >= -sDeadZone && sRightThumbStick.x <= 0.0f && sOldButtonStates[19])
									UpdateButtonState(19, false);

								if (sRightThumbStick.x > sDeadZone)
									UpdateButtonState(20, true);
								else if (sRightThumbStick.x >= 0.0f && sRightThumbStick.x <= sDeadZone && sOldButtonStates[20])
									UpdateButtonState(20, false);

								break;
							}
							case SDL_CONTROLLER_AXIS_RIGHTY:
							{
								sRightThumbStick.y = sdl_event.caxis.value / 32767.0f;

								if (sRightThumbStick.y < -sDeadZone)
									UpdateButtonState(21, true);
								else if (sRightThumbStick.y >= -sDeadZone && sRightThumbStick.y <= 0.0f && sOldButtonStates[21])
									UpdateButtonState(21, false);

								if (sRightThumbStick.y > sDeadZone)
									UpdateButtonState(22, true);
								else if (sRightThumbStick.y >= 0.0f && sRightThumbStick.y <= sDeadZone && sOldButtonStates[22])
									UpdateButtonState(22, false);

								break;
							}
							case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
							{
								sLeftTrigger = sdl_event.caxis.value / 32767.0f;
								break;
							}
							case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
							{
								sRightTrigger = sdl_event.caxis.value / 32767.0f;
								break;
							}
						}
						break;
					}
				}
			}

			for (int i = 0; i <= 22; i++)
				Input::Scan(sButtonStates[i], sOldButtonStates[i], sNewButtonStates[i]);
		}
	}

	void Gamepad::Close()
	{
		SDL_GameControllerClose(sController);
	}
}


