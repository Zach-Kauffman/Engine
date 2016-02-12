
#pragma once

//project includes
	//include base class
	#include "Objects/Object.hpp"	//gets most dependencies from here. Should they be locally #included?

	//XML parser
	#include "Utility/XMLParser.hpp"
	
	//resource maanger
	#include "ResourceManager/ResourceManager.hpp"

	//layer
	#include "Layers/Layer.hpp"

//SFML includes
#include <SFML/Graphics.hpp>

namespace objects
{
//class for testing ObjectManager/group and so on
	class MovingTestObject : public Object
	{
	public:
		MovingTestObject();
		~MovingTestObject();

		void draw(Layer& renderTarget);
		void update(std::vector<int>& fkeyVec);

		void load(boost::property_tree::ptree& dataTree, ResourceManager& resources);	//loads instances object properties based on subtree
		void write();

		sf::Vector2f* getPositionPtr();


	private:
		void move(const sf::Vector2f& dist);
		void move(const float& dist_x, const float& dist_y);
		int ID;

		const sf::Texture* testTex;
		sf::VertexArray texCoords;

		sf::Vector2f position;

		double counter = 0;
	};
}