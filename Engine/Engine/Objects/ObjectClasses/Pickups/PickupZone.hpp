#pragma once
#include "Pickup.hpp"

namespace objects
{

	class PickupZone : public Object
	{
	public:
		PickupZone();
		~PickupZone();

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rman);
		boost::property_tree::ptree write();

		Pickup generatePickup();


	private:

		void createDistribution();

		bool displaying;

		const sf::Texture* pZoneTexture;
		sf::VertexArray textureCoords;
		std::string textureName;


		double yVal;
		double xValLeft;
		double xValRight;

		std::string seasonName;

		std::map<std::string, double> distribution;

	};



}


