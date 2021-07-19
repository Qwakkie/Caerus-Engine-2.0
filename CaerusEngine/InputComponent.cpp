#include "CaerusPCH.h"
#include "InputComponent.h"

#include "Command.h"

InputComponent::~InputComponent()
{
	for (auto pair : m_pActions)
		delete pair.second;
}

void InputComponent::Update(float)
{
	const InputManager& input{ InputManager::GetInstance() };
	for(auto& pair : m_pActions)
	{
		if (input.IsTriggered(pair.first))
			pair.second->Execute(m_pParent);
	}
}

void InputComponent::AddCommand(TriggerState state, ControllerButton button, int key, Command* pCommand)
{
	m_pActions[{m_ActionAmount, state, button, key}] = pCommand;
	++m_ActionAmount;
}
