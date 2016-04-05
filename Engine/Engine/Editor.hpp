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

#include "EditorGUI.hpp"


typedef std::map<std::string, std::string> StringMap;
typedef std::tuple<boost::property_tree::ptree, StringMap > SelectionData;

class Editor : public Game
{
public:
	Editor();
	~Editor();

	void editorInitialize();
	void editorBegin();
	void editorUpdate();
	void editorDraw();


	void updateSelection();		//deduces and updates the currently selected object or resource

	void promptObjectType();
	void addObject();
	void editObject();
	void removeObject();
	void updateObject();
	void selectObject(const int& ID);

	void loadAttributes(const std::string& path);
	void saveObjects();
	void loadSavedObjects();

	void promptResourceName();
	void addResource();			//all actions apply to currently selected resource
	void editResource();
	void updateResource();
	void removeResource();
	void selectResource(const std::string& name);

	void saveResources();
	void loadSavedResources();

private:
	void parsePopupOutput();
	void resetMap(StringMap& smap);



	int currentLayer;		//currently selected layer

	//first value of property map will always be two integers seperated by colon representing chunk eg (10:4) would be chunkX = 10 chunkY = 4
	//second value will always be layer
	StringMap* objProperties;				//currently selected object's property list
	boost::property_tree::ptree* objXml;	//currently selected object's xml

	StringMap objIDMap;						//map for object selection by id with EntryTable
	int objID;								//currently selected object's id

	StringMap currentLayerMap;				//map for layer selection with EntryTable
	bool layerChanged;

	StringMap currentRecMap;
	std::string currentRecName;

	bool objSelection;	//true if object is currently selected
	bool recSelection;	//true if resource is currently selected

	std::map<std::string, StringMap > objectAttributes;		//key is name, second map is attribute list(key is xml name, second is input storage)
	std::map<std::string, SelectionData&> objectList;		//list of created objects with xml and string maps -- key value is string path to object in objMan
	std::map<int, SelectionData> idList;					//same list with real data and ids as the key values
		
	std::map<std::string, SelectionData> resourceList;

	EditorGUI gui;
	std::string popData;	//data retrieved from popup
	int popInfoType;		//0 is object type 1 is resource types 2 is for deletetion confirmation .....	interpreted in parsePopupOutput()
	StringMap objectPrompt;		//popup prompt for new object
	StringMap resourcePrompt;	//popup prompt for new resource
	StringMap deletePrompt;		//popup prompt for deletion confirmation

};