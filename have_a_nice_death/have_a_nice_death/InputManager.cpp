#include "pch.h"
#include "InputManager.h"
#include "Game.h"

void InputManager::Init(HWND hwnd, HWND subhwnd)
{
	_hwnd = hwnd;
	_subhwnd = subhwnd;

	_states.resize(KEY_TYPE_COUNT, KeyState::None);

}

void InputManager::Update(HWND hwnd)
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 UP
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos); // 커서의 좌표를 알아온다
	::ScreenToClient(_hwnd, &_mousePos);

	if (GetButtonDown(KeyType::LeftMouse))
	{
		//눌린 좌표가, 게임 시작인지, 게임 에디터 인지는 알아야지
		if (hwnd == _hwnd)
		{
			Game::GetInstance()->OnLeftClickEvent();
		}
	}

	else if (GetButtonDown(KeyType::RightMouse))
	{
		if (hwnd == _hwnd)
		{
			Game::GetInstance()->OnRightClickEvent();
		}
	}
}

int32 InputManager::GetMovePressedX() const
{
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
	{
		return -1;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		return 1;
	}
	return 0;
}

int32 InputManager::GetMoveDownX() const
{
	if (InputManager::GetInstance()->GetButtonDown(KeyType::Left))
	{
		return -1;
	}
	if (InputManager::GetInstance()->GetButtonDown(KeyType::Right))
	{
		return 1;
	}
	return 0;
}
