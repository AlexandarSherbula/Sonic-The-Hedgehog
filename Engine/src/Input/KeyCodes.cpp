#include "aio_pch.h"
#include "KeyCodes.h"

#include <Xinput.h>

namespace Alexio
{
	void SetGLFWKeyCodes(std::unordered_map<size_t, int8_t>& mapKeys)
	{
		mapKeys[0x00] = Key::NONE;

		mapKeys[GLFW_KEY_F1] = Key::F1; mapKeys[GLFW_KEY_F2] = Key::F2; mapKeys[GLFW_KEY_F3] = Key::F3; mapKeys[GLFW_KEY_F4] = Key::F4;
		mapKeys[GLFW_KEY_F5] = Key::F5; mapKeys[GLFW_KEY_F6] = Key::F6; mapKeys[GLFW_KEY_F7] = Key::F7; mapKeys[GLFW_KEY_F8] = Key::F8;
		mapKeys[GLFW_KEY_F9] = Key::F9; mapKeys[GLFW_KEY_F10] = Key::F10; mapKeys[GLFW_KEY_F11] = Key::F11; mapKeys[GLFW_KEY_F12] = Key::F12;

		mapKeys[GLFW_KEY_DOWN] = Key::DOWN; mapKeys[GLFW_KEY_LEFT] = Key::LEFT; mapKeys[GLFW_KEY_RIGHT] = Key::RIGHT; mapKeys[GLFW_KEY_UP] = Key::UP;		

		mapKeys[GLFW_KEY_BACKSPACE] = Key::BACK; mapKeys[GLFW_KEY_ESCAPE] = Key::ESCAPE; mapKeys[GLFW_KEY_ENTER] = Key::ENTER; mapKeys[GLFW_KEY_PAUSE] = Key::PAUSE;
		mapKeys[GLFW_KEY_SCROLL_LOCK] = Key::SCROLL; mapKeys[GLFW_KEY_TAB] = Key::TAB; mapKeys[GLFW_KEY_DELETE] = Key::DEL; mapKeys[GLFW_KEY_HOME] = Key::HOME;
		mapKeys[GLFW_KEY_END] = Key::END; mapKeys[VK_PRIOR] = Key::PGUP; mapKeys[VK_NEXT] = Key::PGDN; mapKeys[VK_INSERT] = Key::INS;
		mapKeys[GLFW_KEY_LEFT_SHIFT] = Key::L_SHIFT; mapKeys[GLFW_KEY_RIGHT_SHIFT] = Key::R_SHIFT;
		mapKeys[GLFW_KEY_LEFT_CONTROL] = Key::L_CTRL; mapKeys[GLFW_KEY_RIGHT_CONTROL] = Key::R_CTRL;
		mapKeys[GLFW_KEY_LEFT_ALT] = Key::L_ALT; mapKeys[GLFW_KEY_RIGHT_ALT] = Key::R_ALT;
		mapKeys[GLFW_KEY_SPACE] = Key::SPACE;

		mapKeys[GLFW_KEY_0] = Key::K0; mapKeys[GLFW_KEY_1] = Key::K1; mapKeys[GLFW_KEY_2] = Key::K2; mapKeys[GLFW_KEY_3] = Key::K3; mapKeys[GLFW_KEY_4] = Key::K4;
		mapKeys[GLFW_KEY_5] = Key::K5; mapKeys[GLFW_KEY_6] = Key::K6; mapKeys[GLFW_KEY_7] = Key::K7; mapKeys[GLFW_KEY_8] = Key::K8; mapKeys[GLFW_KEY_9] = Key::K9;

		mapKeys[GLFW_KEY_KP_0] = Key::NP0; mapKeys[GLFW_KEY_KP_1] = Key::NP1; mapKeys[GLFW_KEY_KP_2] = Key::NP2; mapKeys[GLFW_KEY_KP_3] = Key::NP3; mapKeys[GLFW_KEY_KP_4] = Key::NP4;
		mapKeys[GLFW_KEY_KP_5] = Key::NP5; mapKeys[GLFW_KEY_KP_6] = Key::NP6; mapKeys[GLFW_KEY_KP_7] = Key::NP7; mapKeys[GLFW_KEY_KP_8] = Key::NP8; mapKeys[GLFW_KEY_KP_9] = Key::NP9;
		mapKeys[GLFW_KEY_KP_MULTIPLY] = Key::NP_MUL; mapKeys[GLFW_KEY_KP_ADD] = Key::NP_ADD; mapKeys[GLFW_KEY_KP_DIVIDE] = Key::NP_DIV; mapKeys[GLFW_KEY_KP_SUBTRACT] = Key::NP_SUB; mapKeys[GLFW_KEY_KP_DECIMAL] = Key::NP_DECIMAL;
		

		mapKeys[GLFW_KEY_SEMICOLON] =	   Key::SEMICOLON;		// On US and UK keyboards this is the ';:' key
		mapKeys[GLFW_KEY_SLASH] =		   Key::SLASH;			// On US and UK keyboards this is the '/?' key
		mapKeys[GLFW_KEY_GRAVE_ACCENT] =   Key::BACKTICK;		// On US keyboard this is the '~' key
		mapKeys[GLFW_KEY_LEFT_BRACKET] =   Key::LBRACKET;		// On US and UK keyboards this is the '[{' key
		mapKeys[GLFW_KEY_BACKSLASH] =	   Key::BACKSLASH;		// On US keyboard this is '\|' key.
		mapKeys[GLFW_KEY_RIGHT_BRACKET] =  Key::RBRACKET;		// On US and UK keyboards this is the ']}' key
		mapKeys[GLFW_KEY_APOSTROPHE] =	   Key::APOSTROPHE;		// On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
		mapKeys[GLFW_KEY_WORLD_1] =		   Key::OEM_8;			// miscellaneous characters. Varies by keyboard
		mapKeys[GLFW_KEY_EQUAL] =		   Key::EQUALS;			// the '+' key on any keyboard
		mapKeys[GLFW_KEY_COMMA] =		   Key::COMMA;			// the comma key on any keyboard
		mapKeys[GLFW_KEY_MINUS] =		   Key::MINUS;			// the minus key on any keyboard
		mapKeys[GLFW_KEY_PERIOD] =		   Key::PERIOD;			// the period key on any keyboard
		mapKeys[GLFW_KEY_CAPS_LOCK] =	   Key::CAPS_LOCK;
	}


#ifdef AIO_PLATFORM_WINDOWS
	void SetWin32KeyCodes(std::unordered_map<size_t, int8_t>& mapKeys)
	{
		mapKeys[0x00] = Key::NONE;	

		mapKeys[VK_F1] = Key::F1; mapKeys[VK_F2] = Key::F2; mapKeys[VK_F3] = Key::F3; mapKeys[VK_F4] = Key::F4;
		mapKeys[VK_F5] = Key::F5; mapKeys[VK_F6] = Key::F6; mapKeys[VK_F7] = Key::F7; mapKeys[VK_F8] = Key::F8;
		mapKeys[VK_F9] = Key::F9; mapKeys[VK_F10] = Key::F10; mapKeys[VK_F11] = Key::F11; mapKeys[VK_F12] = Key::F12;

		mapKeys[VK_DOWN] = Key::DOWN; mapKeys[VK_LEFT] = Key::LEFT; mapKeys[VK_RIGHT] = Key::RIGHT; mapKeys[VK_UP] = Key::UP;		

		mapKeys[VK_BACK] = Key::BACK; mapKeys[VK_ESCAPE] = Key::ESCAPE; mapKeys[VK_RETURN] = Key::ENTER; mapKeys[VK_PAUSE] = Key::PAUSE;
		mapKeys[VK_SCROLL] = Key::SCROLL; mapKeys[VK_TAB] = Key::TAB; mapKeys[VK_DELETE] = Key::DEL; mapKeys[VK_HOME] = Key::HOME;
		mapKeys[VK_END] = Key::END; mapKeys[VK_PRIOR] = Key::PGUP; mapKeys[VK_NEXT] = Key::PGDN; mapKeys[VK_INSERT] = Key::INS;
		mapKeys[VK_LSHIFT] = Key::L_SHIFT; mapKeys[VK_RSHIFT] = Key::R_SHIFT; 
		mapKeys[VK_LCONTROL] = Key::L_CTRL; mapKeys[VK_RCONTROL] = Key::R_CTRL;
		mapKeys[VK_LMENU] = Key::L_ALT; mapKeys[VK_RMENU] = Key::R_ALT;
		mapKeys[VK_SPACE] = Key::SPACE;

		mapKeys[0x30] = Key::K0; mapKeys[0x31] = Key::K1; mapKeys[0x32] = Key::K2; mapKeys[0x33] = Key::K3; mapKeys[0x34] = Key::K4;
		mapKeys[0x35] = Key::K5; mapKeys[0x36] = Key::K6; mapKeys[0x37] = Key::K7; mapKeys[0x38] = Key::K8; mapKeys[0x39] = Key::K9;

		mapKeys[VK_NUMPAD0] = Key::NP0; mapKeys[VK_NUMPAD1] = Key::NP1; mapKeys[VK_NUMPAD2] = Key::NP2; mapKeys[VK_NUMPAD3] = Key::NP3; mapKeys[VK_NUMPAD4] = Key::NP4;
		mapKeys[VK_NUMPAD5] = Key::NP5; mapKeys[VK_NUMPAD6] = Key::NP6; mapKeys[VK_NUMPAD7] = Key::NP7; mapKeys[VK_NUMPAD8] = Key::NP8; mapKeys[VK_NUMPAD9] = Key::NP9;
		mapKeys[VK_MULTIPLY] = Key::NP_MUL; mapKeys[VK_ADD] = Key::NP_ADD; mapKeys[VK_DIVIDE] = Key::NP_DIV; mapKeys[VK_SUBTRACT] = Key::NP_SUB; mapKeys[VK_DECIMAL] = Key::NP_DECIMAL;

		
		mapKeys[VK_OEM_1] =			Key::SEMICOLON;		// On US and UK keyboards this is the ';:' key
		mapKeys[VK_OEM_2] =			Key::SLASH;			// On US and UK keyboards this is the '/?' key
		mapKeys[VK_OEM_3] =			Key::BACKTICK;		// On US keyboard this is the '~' key
		mapKeys[VK_OEM_4] =			Key::LBRACKET;		// On US and UK keyboards this is the '[{' key
		mapKeys[VK_OEM_5] =			Key::BACKSLASH;		// On US keyboard this is '\|' key.
		mapKeys[VK_OEM_6] =			Key::RBRACKET;		// On US and UK keyboards this is the ']}' key
		mapKeys[VK_OEM_7] =			Key::APOSTROPHE;	// On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
		mapKeys[VK_OEM_8] =			Key::OEM_8;			// miscellaneous characters. Varies by keyboard
		mapKeys[VK_OEM_PLUS] =		Key::EQUALS;		// the '+' key on any keyboard
		mapKeys[VK_OEM_COMMA] =		Key::COMMA;			// the comma key on any keyboard
		mapKeys[VK_OEM_MINUS] =		Key::MINUS;			// the minus key on any keyboard
		mapKeys[VK_OEM_PERIOD] =	Key::PERIOD;		// the period key on any keyboard
		mapKeys[VK_CAPITAL] =		Key::CAPS_LOCK;
	}
#endif
}

