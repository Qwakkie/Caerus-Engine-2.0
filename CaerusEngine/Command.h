#pragma once

class GameObject;

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	Command(Command& other) = default;
	Command(Command&& other) = default;
	Command& operator=(const Command& other) = default;
	Command& operator=(Command&& other) = default;

	virtual void Execute(GameObject*) = 0;
};