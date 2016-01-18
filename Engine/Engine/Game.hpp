#pragma once

//boost includes
#include <boost\shared_ptr.hpp>

//SFML includes
#include <SFML\Graphics.hpp>

//project includes
	#include "Defines.hpp"

	//basic management classes
	#include "ObjectManager.hpp"
	#include "Layers\LayerManager.hpp"
	#include "ResourceManager\ResourceManager.hpp"

	//utility classes
	#include "Utilities.hpp"
	#include "INIParser.hpp"
	#include "Logger.hpp"

class Game
{
public:
	Game();
	~Game();

	void initialize(const std::string& configFile, const std::string& mapFile, const std::string& saveFile, const bool& doLoadScreen);	//initializes the game and begins loading of objects
	void begin();																						//fgvr

private:

	void draw();			//renders drawables to screen
	void update();			//calculates physics, item interactions, etc

	void loadGameConfig(const std::string& configFile);	//loads basic game settings
	void loadResources();	//loads all textures, shaders, etc
	void loadObjects();		//initializes object base types
	void loadMap();			//loads basic map information


	boost::shared_ptr<sf::RenderWindow> windowPtr;
	objects::ObjectManager objMan;
	LayerManager layMan;
	ResourceManager recMan;

	std::string windowName;		//name of the window
	sf::Vector2i renderSize;	//resolution of game
	int maxFPS;					//fps cap - 0 would mean uncapped

	
};