/*
	Author: Derek Ackworth
	Date: April 18th, 2019
	File: Subject.hpp
	Purpose: Subject class declaration
*/

#pragma once

#include <typeinfo>
#include <set>
#include <string>
#include "Observer.hpp"

using namespace std;

class Subject
{
public:
	void attach(Observer* oPtr) { observers_.insert(oPtr); }
	void detach(Observer* oPtr) { observers_.erase(oPtr); }
	void notifyAll();
	void notify(string className);

private:
	set<Observer*> observers_;
};
