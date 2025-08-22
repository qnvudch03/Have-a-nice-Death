#pragma once
#include "Singleton.h"

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	KeepUp = '.',
	Down = VK_DOWN,
	KeepLeft = '-',
	KeepRight = '*',
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,
	Shift = VK_SHIFT,

	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,

	KEY_1 = '1',
	KEY_2 = '2',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Inventory = 'I',
	Z = 'Z',
	X = 'x',
	E = 'E',

	NumPad2 = VK_NUMPAD2,
	NumPad8 = VK_NUMPAD8,

	RELEASE = '0',

	MAX,
};

enum class KeyState
{
	None,
	Press,
	Down,
	Up,

	End
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

class InputManager : public Singleton<InputManager>
{
public:
	void Init(HWND hwnd, HWND subhwnd);
	void Update(HWND hwnd);

	// 누르고 있을 때
	bool GetButtonPressed(KeyType key) { return GetState(key) == KeyState::Press; }

	// 맨 처음 눌렀을 때
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 맨 처음 눌렀다가 땔 때
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

	// 이동 입력키가 눌려있는지
	int32 GetMovePressedX() const;
	int32 GetMoveDownX() const;
	int32 GetMoveDirY() const;

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;
	HWND _subhwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos = {};
};

