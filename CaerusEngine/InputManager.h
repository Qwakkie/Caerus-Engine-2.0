#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include "Singleton.h"

class Command;

enum class ControllerButton
{
	ButtonUp = 0,
	ButtonDown = 1,
	ButtonLeft = 2,
	ButtonRight = 3,

	ButtonStart = 4,
	ButtonBack = 5,
	
	ButtonLeftThumb = 6,
	ButtonRightThumb = 7,

	ButtonLeftShoulder = 8,
	ButtonRightShoulder = 9,
	
	ButtonA = 12,
	ButtonB = 13,
	ButtonX = 14,
	ButtonY = 15
};

enum class TriggerState
{
	Pressed,
	Released,
	Down
};


struct InputAction
{
	TriggerState state;
	ControllerButton button;
	int key;
};

inline bool operator<(InputAction left, InputAction right)
{
	return (static_cast<int>(left.button) + left.key) < (static_cast<int>(right.button) + right.key);
}

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();
	
	bool ProcessInput();
	bool IsTriggered(InputAction) const;
private:
	XINPUT_STATE m_CurrentControllerState{};
	XINPUT_STATE m_PreviousControllerState{};
	PBYTE m_pCurrentKeyboardState{};
	PBYTE m_pOldKeyboardState{};

	PBYTE m_pKeyboardStateA;
	PBYTE m_pKeyboardStateB;
	bool m_KeyboardStateBActive{};
};
