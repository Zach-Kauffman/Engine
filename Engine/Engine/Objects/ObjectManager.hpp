#pragma once

//boost stuff
#include "boost\shared_ptr.hpp"
#include "boost\function.hpp"

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

		int nextID(); //returns the next ID to be issued and increments ID
		int getCurrentID(); 

		boost::shared_ptr<Object> getPrototype(const std::string& type);

		template<class T>
		void addPrototype(const std::string& type)
		{
			if (prototypes.find(type) != prototypes.end())	//if the object is found
			{
				//give an error because it cannot be added
				BOOST_LOG_SEV(*groupLogger, ERROR) << "Object (type = " << type << " ) was not added to prototype list: an object with that key was found";
			}
			else
			{
				prototypes[type] = &ObjectManager::instancePrototype<T>;	//define
			}
		}
	private:
		template<class derived>
		Object* instancePrototype()		//return raw pointer to child of Object
		{
			return new derived();
		}


		std::map<std::string, Object*(ObjectManager::*)()> prototypes;
		//boost::shared_ptr<Object>(ObjectManager::*makeObject)()

		src::severity_logger<severity_level> objectLogger;				//real logger object -- passed to all objectGroups

		int currentID;
	};
}




