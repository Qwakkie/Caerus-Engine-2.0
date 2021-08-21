#include "CaerusPCH.h"
#include "InputManager.h"

InputManager::InputManager()
{
	m_pKeyboardStateA = new BYTE[256];
	m_pKeyboardStateB = new BYTE[256];

	const bool gotKeyboardState = GetKeyboardState(m_pKeyboardStateA) && GetKeyboardState(m_pKeyboardStateB);

	if(!gotKeyboardState)
	{
		throw std::runtime_error("InputManager::InputManager() > Failed to get keyboard state");
	}
}


bool InputManager::ProcessInput()
{
	m_PreviousControllerState = m_CurrentControllerState;
	ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentControllerState);

	BOOL getKeyboardResult;
	if (m_KeyboardStateBActive)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardStateA);
		m_pOldKeyboardState = m_pKeyboardStateB;
		m_pCurrentKeyboardState = m_pKeyboardStateA;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardStateB);
		m_pOldKeyboardState = m_pKeyboardStateA;
		m_pCurrentKeyboardState = m_pKeyboardStateB;
	}

	m_KeyboardStateBActive = !m_KeyboardStateBActive;
	
	if(!getKeyboardResult)
	{
		throw std::runtime_error("InputManager::ProcessInput > Failed to get keyboard state");
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

bool InputManager::IsTriggered(InputAction action) const
{
	switch (action.state)
	{
	case TriggerState::Down:
		return m_CurrentControllerState.Gamepad.wButtons & (1 << static_cast<int>(action.button)) || m_pCurrentKeyboardState[action.key] & 0xF0;
	case TriggerState::Pressed:
		return m_CurrentControllerState.Gamepad.wButtons & (1 << static_cast<int>(action.button)) && !(m_PreviousControllerState.Gamepad.wButtons & (1 << static_cast<int>(action.button)))
			|| m_pCurrentKeyboardState[action.key] & 0xF0 && !(m_pOldKeyboardState[action.key] & 0xF0);
	case TriggerState::Released:
		return !(m_CurrentControllerState.Gamepad.wButtons & (1 << static_cast<int>(action.button))) && m_PreviousControllerState.Gamepad.wButtons & (1 << static_cast<int>(action.button))
		|| !(m_pCurrentKeyboardState[action.key] & 0xF0) && m_pOldKeyboardState[action.key] & 0xF0;
	default:
		return false;
	}
}

