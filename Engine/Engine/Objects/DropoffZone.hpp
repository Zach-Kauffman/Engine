#pragma once

#include "Object.hpp"
#include "Physics/Collision/Collidable.hpp"
#include "ObjectClasses/Pickups/Pickup.hpp"

namespace objects
{
	class DropoffZone : public Collidable, public Object
	{
	public:
		DropoffZone();
		~DropoffZone();

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rman);

	private:
		boost::shared_ptr
	};
}
