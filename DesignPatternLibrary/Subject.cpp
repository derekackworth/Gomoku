/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Subject.cpp
	Purpose: Subject class implementation
*/

#include "Subject.hpp"

// Notify all observers
void Subject::notifyAll()
{
	for (auto observer : observers_)
		observer->update();
}

/*
	Notify specific observer
	Input: Class name to notify
*/
void Subject::notify(string className)
{
	for (auto observer : observers_)
	{
		string observerName = typeid(*observer).name();

		if (observerName == className)
		{
			observer->update();
		}
	}
}
