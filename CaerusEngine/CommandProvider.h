#pragma once
#include <vector>

class GameObject;
class Command;

class CommandProvider
{
public:
	CommandProvider() = default;
	virtual ~CommandProvider();

	CommandProvider(CommandProvider&) = delete;
	CommandProvider(CommandProvider&&) = delete;
	CommandProvider& operator=(CommandProvider&) = delete;
	CommandProvider& operator=(CommandProvider&&) = delete;
	
	virtual Command* GetCurrentCommand(GameObject* pActor, GameObject* pTarget) = 0;
protected:
	std::vector<Command*> m_pCommands{};
};

