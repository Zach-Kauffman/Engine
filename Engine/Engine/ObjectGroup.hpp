#pragma once

//standard includes
#include <vector>
#include <string> 

//boost stuff
#include "boost\shared_ptr.hpp"

//project includes
#include "Object.hpp"
#include "NameSearchable\NameSearchable.hpp"

//This class is a way to organize various groups of objects, for example 
//you may want a group 
class ObjectGroup : public NameSearchable	
{
public:
	ObjectGroup();
	~ObjectGroup();

	//object vector manipulation functions
	void addObject(Object& toAdd);	//adds object to objects vector
	void removeObject()				//simply removes object from "objects" vector

	//object group vector manipulation functions
	void addObjectGroup(const ObjectGroup& newGroup, const std::string& name);	//adds new group to "groups" vector
	void deleteObjectGroup(const std::string& groupName)						//physically deallocates specified objectGroup from memory
private:
	std::vector<boost::shared_ptr<Object>> objects;		//flexible safe pointers to objects
	std::vector<ObjectGroup> groups;					//nesting object group vector this is named using name searchable
	
	//SHOULD OBJECT GROUP HAVE ITS OWN REAL LOGGER?
	boost::shared_ptr<src::severity_logger<severity_level>> groupLogger;	//local pointer to logger contained in ObjectManager 
};

