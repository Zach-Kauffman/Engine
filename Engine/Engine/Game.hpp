#pragma once

//boost includes
#include <boost\shared_ptr.hpp>

//SFML includes
#include <SFML\Graphics.hpp>

//project includes
	#include "Defines.hpp"

	//basic management classes
	#include "Objects\ObjectManager.hpp"
	#include "Layers\LayerManager.hpp"
	#include "ResourceManager\ResourceManager.hpp"

	//utility classes
	#include "Utility\Utilities.hpp"
	#include "Utility\INIParser.hpp"
	#include "Utility\Logger.hpp"
	#include "Utility\XMLParser.hpp"

	#include "Input\KeyboardData.hpp"
	#include "Input\MouseData.hpp"

	#include "MenuStuff\MenuManager.h"

#include "TableEntry\EntryTable.hpp"

class Game
{
public:
	Game();
	~Game();

	void initialize(const std::string& cfgFile, const std::string& resFile, const std::string& objFile, const std::string& mpFile, const std::string& save, const bool& doLoadScreen);	//initializes the game and begins loading of objects
	void begin();			//starts sfml main loop

private:

	void draw();			//renders drawables to screen
	void update();			//calculates physics, item interactions, etc
	void loadGameConfig(const std::string& configFile);	//loads basic game settings
	void loadResources();	//loads all textures, shaders, etc
	void loadObjects();		//initializes object base types
	void loadMap();			//loads basic map information
	void loadEntryTable();

	void updateMap();		//finds new bounds and adds/removes objects

	std::string configFile;
	std::string resourceFile;
	std::string objectFile;
	std::string mapFile;
	std::string saveFile;


	boost::shared_ptr<sf::RenderWindow> windowPtr;
	objects::ObjectManager objMan;
	LayerManager layMan;
	ResourceManager recMan;
	EntryTable gui;

	std::string windowName;		//name of the window
	sf::Vector2i renderSize;	//resolution of game
	int maxFPS;					//fps cap - 0 would mean uncapped

	sf::Vector2f tmpCenter;


	int numLayers;



	std::map<std::string, std::string> testMap;

	KeyboardData keyData;
	MouseData mouseData;
	std::string textDataStr;
	char textDataChr;

	
};