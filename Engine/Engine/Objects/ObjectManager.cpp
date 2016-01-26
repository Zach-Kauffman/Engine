#include "ObjectManager.hpp"

using namespace objects;

//PUBLIC FUNCTIONS

ObjectManager::ObjectManager()	//default constructor
{
	currentID = 0;	//first ID issued will be "1"
	groupLogger.reset(new src::severity_logger<severity_level>());	//groupLogger must be explicitly defined since the overloaded constructor wasn't called
	BOOST_LOG_SEV(*groupLogger, DEBUG) << "ObjectManager Initialized...";
	
}
ObjectManager::~ObjectManager(){}	//default destructor

int ObjectManager::nextID()
{
	BOOST_LOG_SEV(*groupLogger, DEBUG) << "Returning ID #" << currentID+1;
	return ++currentID;
}

boost::shared_ptr<Object> ObjectManager::getPrototype(const std::string& type)
{
	if (prototypes.find(type) != prototypes.end())	//if the value exists in the map
	{
		return prototypes[type]();
	}
	else    //if the string matches no key value the type must not exist
	{
		BOOST_LOG_SEV(*groupLogger, WARNING) << "String to Object lookup (type = " << type << " ) failed. Type does not exist in lookup table. Returning null...";

		return boost::shared_ptr<objects::Object>();	//return null ptr -- error handling in recieving functions

	}
}
