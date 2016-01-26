#pragma once

//project includes
	//include base class
	#include "Objects/Object.hpp"	//gets most dependencies from here. Should they be locally #included?

	//XML parser
	#include "Utility/XMLParser.hpp"
	
	//resource maanger
	#include "ResourceManager/ResourceManager.hpp"

//SFML includes
#include <SFML/Graphics.hpp>

namespace objects
{
//class for testing ObjectManager/group and so on
	class TestObject : public Object
	{
	public:
		TestObject();
		~TestObject();

		void draw(sf::RenderTexture& renderTarget);
		void update();

		void load(boost::property_tree::ptree propertyTree, ResourceGroup& resources);	//loads instances object properties based on subtree
		void write();


	private:
		int ID;

		const sf::Texture* testTex;
		sf::VertexArray texCoords;

		sf::Vector2f position;
	};
}