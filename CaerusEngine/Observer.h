#pragma once
#include <iostream>
class GameObject;

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;

	Observer(Observer&) = default;
	Observer(Observer&&) = default;
	Observer& operator=(const Observer&) = default;
	Observer& operator=(Observer&&) = default;
	
	virtual void Notify(GameObject*, int eventId) = 0;
};