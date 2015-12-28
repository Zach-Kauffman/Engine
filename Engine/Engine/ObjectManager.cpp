#include "ObjectManager.hpp"

using namespace objects;

//PUBLIC FUNCTIONS

ObjectManager::ObjectManager()	//default constructor
{
	boost::shared_ptr<src::severity_logger<severity_level>> tmp(new src::severity_logger<severity_level>());
	groupLogger = tmp;	//groupLogger must be explicitly defined since the overloaded constructor wasn't called
}
ObjectManager::~ObjectManager(){}	//default destructor

int ObjectManager::nextID()
{
	return ++currentID;
}
