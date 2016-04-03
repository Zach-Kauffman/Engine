#include "Object.hpp"

using namespace objects;

Object::Object()
{
	
}

Object::~Object(){}

int Object::getID()
{
	std::cout << &ID << ", ";
	return ID;
}

void Object::setID(int newID)
{
	ID = newID;
}

bool Object::getActive()
{
	return isActive;
}

void Object::setActive(bool activity)
{
	isActive = activity;
}
