#pragma once

namespace Alexio
{
	struct States
	{
		bool pressed = false;
		bool held = false;
		bool released = false;
	};
}

enum Key
{
	NONE,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	UP, DOWN, LEFT, RIGHT,
	SPACE, TAB, L_SHIFT, R_SHIFT, L_CTRL, R_CTRL, L_ALT, R_ALT, INS, DEL, HOME, END, PGUP, PGDN,
	BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
	NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
	NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
	EQUALS, COMMA, MINUS,
	SEMICOLON, SLASH, BACKTICK, LBRACKET, BACKSLASH, RBRACKET, APOSTROPHE, OEM_8,
	CAPS_LOCK, ENUM_END
};

enum MouseButton
{
	L_BUTTON,
	R_BUTTON,
	M_BUTTON,
	X_BUTTON1,
	X_BUTTON2,
	X_BUTTON3,
	X_BUTTON4,
	X_BUTTON5,
};

// Gamepad Codes
namespace Generic
{
	enum
	{
		FACE_DOWN,
		FACE_RIGHT,
		FACE_LEFT,
		FACE_UP,
		BACK,
		POWER,
		START,
		L_STICK_PUSH,
		R_STICK_PUSH,
		LEFT_SHOULDER,
		RIGHT_SHOULDER,
		D_PAD_UP,
		D_PAD_DOWN,
		D_PAD_LEFT,
		D_PAD_RIGHT,
	};
}

namespace Xbox
{
	enum
	{
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BACK,
		POWER,
		START,
		L_STICK_PUSH,
		R_STICK_PUSH,
		LEFT_SHOULDER,
		RIGHT_SHOULDER,
		D_PAD_UP,
		D_PAD_DOWN,
		D_PAD_LEFT,
		D_PAD_RIGHT
	};
}

namespace PlayStation
{
	enum
	{
		BUTTON_CROSS,
		BUTTON_CIRCLE,
		BUTTON_SQUARE,
		BUTTON_TRIANGLE,
		SELECT,
		SHARE = 4,
		POWER,
		START,
		OPTIONS = 6,
		L3,
		R3,
		L1,
		R1,
		D_PAD_UP,
		D_PAD_DOWN,
		D_PAD_LEFT,
		D_PAD_RIGHT
	};
}


namespace Alexio
{
	void SetGLFWKeyCodes(std::unordered_map<size_t, int8_t>& mapKeys);
#ifdef AIO_PLATFORM_WINDOWS
	void SetWin32KeyCodes(std::unordered_map<size_t, int8_t>& mapKeys);
#endif // ALI_PLATFORM_WINDOWS	
}