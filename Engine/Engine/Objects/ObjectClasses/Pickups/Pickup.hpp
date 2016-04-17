#pragma once
#pragma once
#include "../../Physics/Collision/Collidable.hpp"
#include "../../Object.hpp"

namespace objects
{

	class : public Collidable, public Object
	{
	public:
		Pickup();
		~Pickup();

		void recieveCollisionData(CollisionData*);

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager&);
		boost::property_tree::ptree write();

	private:




	};

}