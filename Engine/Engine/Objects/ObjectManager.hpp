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
