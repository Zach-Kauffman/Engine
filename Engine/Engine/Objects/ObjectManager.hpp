#pragma once

//boost stuff
#include "boost\shared_ptr.hpp"

//project includes
#include "..\Utility\Logger.hpp"
#include "ObjectGroup.hpp"
#include "..\Utility\Downcast.hpp"

namespace objects
{
	class ObjectManager : public ObjectGroup
		//most stuff from ObjectGroup
	{
	public:
		ObjectManager();
		~ObjectManager();

		template<class T>
		void deleteObject(const T& object)		//actually deletes object from memory, careful... this could cause issues :z
												//public alias for delete object from tree
		{
			deleteObjectFromTree(object);
		}						

		int nextID(); //returns the next ID to be issued;

	private:
		src::severity_logger<severity_level> objectLogger;				//real logger object -- passed to all objectGroups

		int currentID;
	};
}

boost::shared_ptr<objects::Object> stringToObject(const std::string& type)
{
	if(type == "testObject")
	{
		return makeObject<objects::TestObject>();	//create and return (uninitialized?) object prototype
	}
	else    //if the string matches none of the cases the type must not exist
	{
		auto slg = logger::getSLogger();
		BOOST_LOG_SEV(slg, WARNING) << "String to Object lookup (type = " << type << " ) failed. Type does not exist. Returning null...";

		return boost::shared_ptr<objects::Object>();	//return null ptr -- error handling in recieving functions
		
	}
}

template<class T> 
boost::shared_ptr<T> makeObject()
{
	return boost::shared_ptr<objects::Object> tmp(new T);
}

