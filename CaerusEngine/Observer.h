#pragma once
#include <iostream>
class GameObject;

enum class Event
{
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_DOWN,
	ACTOR_CREATED,
	ACTOR_DIED,
	ACTOR_MOVED_RIGHT,
	ACTOR_MOVED_LEFT,
	ACTOR_MOVED_UP,
	ACTOR_MOVED_DOWN,
	ACTOR_JUMPED,
	TILE_COLOURED,
	ACTOR_REACHED_BOTTOM,
	ACTOR_JUMPED_OFF
};

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;

	Observer(Observer&) = default;
	Observer(Observer&&) = default;
	Observer& operator=(const Observer&) = default;
	Observer& operator=(Observer&&) = default;
	
	virtual void Notify(GameObject*, Event event) = 0;
};