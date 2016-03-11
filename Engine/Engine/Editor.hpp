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

	#include "Game.hpp"

class Editor : public Game
{
public:
	Editor();
	~Editor();

	
private:
	void editorUpdate();
	void editorDraw();

	void addObject();
	void editObject(std::string& ID);
	void removeObject(std::string& ID);

	void addResource();
	void editResource(std::string& name);
	void removeResource(std::string& name);

	std::map<std::string, std::map<std::string, std::string> > objectAttributes;	//key is name, second map is attribute list(key is xml name, second is input storage)
	
};