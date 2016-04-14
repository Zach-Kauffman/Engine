#pragma once

#include "Physics\Physics.hpp"
#include "Graphics\Graphics.hpp"
#include "Object.hpp"
#include "../Utility/XMLParser.hpp"

namespace objects
{
	class Squirrel : public Object, public Movable
	{
	public:
		Squirrel();
		~Squirrel();

		void draw(Layer& renderTarget);
		void update(InputData& inpData);

		void load(boost::property_tree::ptree& dataTree, ResourceManager& recMan);
		boost::property_tree::ptree write();

	private:
		Animation walking;
		Animation idle;

		float moveSpeed;


		sf::Vector2f displaySize;
		sf::Vector2f frameSize;
		std::string walkingSSName;
		std::string idleSSName;
		int fps;

	};
}
