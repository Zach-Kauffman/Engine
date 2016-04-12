#include "Editor.hpp"

Editor::Editor()
{
	layerChanged = false;
	currentLayer = 1;
	currentLayerMap["Layer"] = "1";

	objID = 1;
	objIDMap["Object ID"] = "1";

	popData = "";
	objectPrompt["Enter Type:"] = "";
	resourcePrompt["Enter Name:"] = "";

	objSelection = false;
	recSelection = false;
}

Editor::~Editor()
{

}

void Editor::editorInitialize()
{
	loadAttributes("attributes.xml");
	gui.initialize(&recMan);
	
	boost::function<void()> boundFxn = boost::bind(&Editor::promptObjectType, this);
	gui.setButtonCallback("editorMenu", "newObject", boundFxn, 12);

	boundFxn = boost::bind(&Editor::updateSelection, this);
	gui.setButtonCallback("editorMenu", "updateButton", boundFxn, 12);

	boundFxn = boost::bind(&Editor::addResource, this);
	gui.setButtonCallback("editorMenu", "newResource", boundFxn, 12);

	boundFxn = boost::bind(&Editor::saveFile, this);
	gui.setButtonCallback("editorMenu", "save", boundFxn, 12);

	gui.setMap("editorMenu", "selectedObject", currentLayerMap, 1);
	gui.setMap("editorMenu", "selectedLayer", objIDMap, 1);
}

void Editor::editorBegin()
{
	selectObject(1);

	sf::RenderWindow& window = *windowPtr;
	window.setKeyRepeatEnabled(false);		//makes it so when a key is hit, only one event is recorded, not nine, or whatever -- ignores holding keys
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)			//KeyCount is the number of Keys; this is intended to check every key
				{
					if (event.key.code == (sf::Keyboard::Key)(i))			//trying to typecast int i as a Key enum 
					{
						inpData.keyPressed(i);

					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
				{
					if (event.key.code == (sf::Keyboard::Key)(i))
					{
						inpData.keyReleased(i);

					}
				}
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					inpData.setTypedChar(static_cast<char>(event.text.unicode));
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				inpData.setMousePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					inpData.setRightData(MouseData::Hit);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					inpData.setLeftData(MouseData::Hit);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					inpData.setRightData(MouseData::Released);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					inpData.setLeftData(MouseData::Released);
				}
			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				inpData.setScroll(event.mouseWheel.delta);
			}

		}

		window.clear();

		if (gui.getPopData())
		{
			parsePopupOutput();
		}

		update();
		editorUpdate();


		draw();
		editorDraw();


		window.display();

		inpData.frameUpdate();
	}
}

void Editor::updateSelection()
{
	if (objSelection != recSelection)	//if they are the same something is wrong nothing happens
	{
		if (objSelection)
		{
			updateObject();
		}
		else if (recSelection)
		{
			updateResource();
		}
	}
}
//update needs to allow for GUI and object selection
void Editor::editorUpdate()
{
	//run selection check for (all???) objects or at least the current layer

	//update gui
	gui.update(inpData);
}

//draw needs to draw GUI
void Editor::editorDraw()
{
	//find object with id of currently selected
	//highlight its rectangle bounds

	gui.draw(*windowPtr);	//tell menus to draw
}

void Editor::promptObjectType()
{
	gui.popup(objectPrompt);	//get that object type
	popInfoType = 0;
}

void Editor::addObject()
{
	popData = objectPrompt.begin()->second;
	//check for type validity

	StringMap properties = objectAttributes[popData];
	boost::property_tree::ptree objectRoot;

	try
	{
		auto tempObject = objMan.getPrototype(popData);
		if (!tempObject){ throw; };
		tempObject->setID(objMan.nextID());
		tempObject->setActive(false);

		idList[tempObject->getID()] = std::make_tuple(objectRoot, properties);
		selectObject(tempObject->getID());

		resetMap(*objProperties);
		gui.setMap("editorMenu", "attributeEditor", *objProperties, 3);	//prompt for all object attributes

		std::string pathString = "Layers.Layer1";// +boost::lexical_cast<std::string>(currentLayer);
		objMan.addObject(tempObject, pathString);
	}
	catch (...){	//catch all exceptions
		BOOST_LOG_SEV(logger, WARNING) << "Object prototype \"" << popData << "\" not found.  Object was not added.";
	}
	//need to catch out of bounds exception coming from prototype creation w/ invalid string	


	//ask for object type
	//get the object stuff and display it with dropdowns options in the gui
	//wait for all input to be complete
	//update object

}

void Editor::editObject()	//edits currently selected object
{
	gui.setMap("editorMenu", "attributeEditor", *objProperties, 3);

	//find object xml by id in storage
	//redisplays option with current selection for editing
	//resaves and updates
}

void Editor::updateObject()
{
	//actually add the object to game with button press
	//construct object property tree
	//create object prototype and load properties
	//display object
	//save tree in temporary location (not in file)(hard to delete there)
	//save xml
	boost::property_tree::ptree newXml;
	std::map<std::string, std::string>::iterator it;
	for (it = objProperties->begin(); it != objProperties->end(); it++)	//iterate through values and store them in property tree
	{
		newXml.put(it->first, it->second);
	}

	objXml = &newXml;

	auto tmp = objMan.getObject(objID);	
	tmp->load(*objXml, recMan);
	tmp->setActive(true);
	//calculate chunk and add here
}

void Editor::selectObject(const int& ID)
{
	SelectionData& toSelect = idList[ID];

	objXml = &std::get<0>(toSelect);
	objProperties = &std::get<1>(toSelect);
	objID = ID;
	objSelection = true;
	recSelection = false;
	objIDMap.begin()->second = boost::lexical_cast<std::string>(ID);

}

void Editor::removeObject()	//deletes object xml and clears id from storage
{
	std::map<std::string, SelectionData&>::iterator it;

	for (it = objectList.begin(); it != objectList.end(); it++)
	{
		if (it->second == idList[objID])
		{
			objectList.erase(it);
		}
	}

	idList.erase(objID);

	objMan.deleteObject(objID);

	
	//could add ctrl-z functionality here
}

void Editor::saveObjects()
{
	std::vector<boost::property_tree::ptree> layers;
	std::vector < std::vector<boost::property_tree::ptree> > chunks;

	for (int layIt = 0; layIt < numLayers; layIt++)
	{

	}
	std::map<int, SelectionData>::iterator it;
	for (it = idList.begin(); it != idList.end(); it++)
	{
		sf::Vector2f chunk;
		std::string chunkStr = std::get<1>(it->second)[""];
		std::vector<std::string> splitChunk = util::splitStrAtSubstr(chunkStr, ":");

		sf::Vector2f loadedChunk;
		if (splitChunk.size() < 2)
		{
			//error -- object chunk data not detected reverting to default (0, 0)
			//revert to default
		}
		else
		{
			loadedChunk = sf::Vector2f(boost::lexical_cast<float>(splitChunk[0]), boost::lexical_cast<float>(splitChunk[1]));
		}
		
		int layer = boost::lexical_cast<int>(std::get<1>(it->second)["layer"]);

		//for (int layer)
	}
}

void Editor::promptResourceName()
{
	gui.popup(resourcePrompt);
}
void Editor::addResource()
{
	popData = resourcePrompt.begin()->second;
	boost::property_tree::ptree filler;
	resourceList[popData] = std::make_tuple(filler, objectAttributes["resource"]);
	selectResource(popData);
	gui.setMap("editorMenu", "attributeEditor", currentRecMap, 1);
}

void Editor::editResource()
{
	gui.setMap("editorMenu", "attributeEditor", currentRecMap, 1);
}

void Editor::updateResource()
{
	//add resource to manager
	recMan.loadFile(currentRecMap["path"], currentRecMap["name"]);
	//make sure it actually added before grouping
	//check if group
		//check for group existence
		//if exists nothing
		//if not create
		//add to group
	
}

void Editor::removeResource()
{

}

void Editor::selectResource(const std::string& name)
{
	currentRecMap.clear();
	currentRecMap = std::get<1>(resourceList[name]);
	currentRecName = name;
	objSelection = false;
	recSelection = true;

}

void Editor::loadAttributes(const std::string& path) //loads object attributes from set of files....??
{
	XMLParser attrLoader("attributes.xml");

	xmlTree<boost::property_tree::ptree> attrTree;

	attrTree.trees["types"];
	attrTree.tags["type"];
	attrTree.trees["types"].trees[""];
	attrTree.trees["types"].tags["attr"];

	attrLoader.getSubTree(attrTree);

	auto& types = attrTree.output;
	auto& attributes = attrTree.trees["types"].output;

	std::string tmp;
	for (int typeIt = 0; typeIt < types[0].size(); typeIt++)
	{
		StringMap attrMap;
		for (int attrIt = 0; attrIt < attributes[typeIt].size(); attrIt++)
		{
			attrLoader.readValue<std::string>("<xmlattr>.attr", tmp, attributes[typeIt][attrIt]);
			attrMap[tmp] = "";
		}
		attrLoader.readValue<std::string>("<xmlattr>.name", tmp, types[0][typeIt]);
		objectAttributes[tmp] = attrMap;
	}

	//for files in directory
	//load file name
	//while getline load attribute to that map
	//done

	//somehow get stringified object prototype names (xml format?)
}

//PRIVATE FUNCTIONS

void Editor::parsePopupOutput()
{
	gui.setPopData(0);

	switch (popInfoType)
	{
	case 0: addObject();
		break;
	case 1: addResource();
		break;
	}
}


void Editor::resetMap(StringMap& smap)
{
	std::map<std::string, std::string>::iterator it;
	for (it = smap.begin(); it != smap.end(); it++)
	{
		smap[it->first] = "";
	}
}