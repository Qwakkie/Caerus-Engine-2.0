#pragma once
#include <map>
#include "Component.h"
#include "InputManager.h"

class Command;

class InputComponent final : public Component
{
public:
	InputComponent() = default;
	~InputComponent();

	InputComponent(InputComponent&) = delete;
	InputComponent(InputComponent&&) = delete;
	InputComponent& operator=(InputComponent&) = delete;
	InputComponent& operator=(InputComponent&&) = delete;

	void Update(float) override;
	
	void AddCommand(TriggerState, ControllerButton, int, Command*);
private:
	std::map<InputAction, Command*> m_pActions{};
	int m_ActionAmount{};
};

