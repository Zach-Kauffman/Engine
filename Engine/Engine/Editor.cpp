#include "Editor.hpp"

Editor::Editor()
{
	objSelection = false;
	loadAllObjects = false;
	loadAllResources = false;
}

Editor::~Editor()
{

}

void Editor::editorInitialize()
{
	gui.initialize(&recMan);
	
	boost::function<void()> boundFxn = boost::bind(&Editor::updateObject, this);
	gui.setButtonCallback("editorMenu", "updateButton", boundFxn, 12);

	boundFxn = boost::bind(&Editor::editObject, this);
	gui.setButtonCallback("editorMenu", "updateButton", boundFxn, 12);

	boundFxn = boost::bind(&Editor::addResource, this);
	gui.setButtonCallback("editorMenu", "save", boundFxn, 12);

	boundFxn = boost::bind(&Editor::saveFile, this);
	gui.setButtonCallback("editorMenu", "save", boundFxn, 12);


	
}

void Editor::editorBegin()
{
	initialize();

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
						keyData.keyPressed(i);

					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
				{
					if (event.key.code == (sf::Keyboard::Key)(i))
					{
						keyData.keyReleased(i);

					}
				}
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					if (event.text.unicode == '\b')
					{
						if (textDataStr.size())
						{
							textDataStr.erase(textDataStr.size() - 1);
						}
					}
					else
					{
						textDataStr += static_cast<char>(event.text.unicode);
					}
					textDataChr = static_cast<char>(event.text.unicode);

				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mouseData.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					mouseData.setRightData(MouseData::Hit);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouseData.setLeftData(MouseData::Hit);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					mouseData.setRightData(MouseData::Released);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouseData.setLeftData(MouseData::Released);
				}
			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				mouseData.setScroll(event.mouseWheel.delta);
			}

		}

		window.clear();

		update();
		editorUpdate();

		draw();
		editorDraw();

		window.display();

		textDataChr = 0;
		keyData.frameUpdate();
		mouseData.frameUpdate();
	}
}

//update needs to allow for GUI and object selection
void Editor::editorUpdate()
{
	//run selection check for (all???) objects or at least the current layer

	//update gui
	gui.update(mouseData, textDataChr, keyData);
}

//draw needs to draw GUI
void Editor::editorDraw()
{
	//find object with id of currently selected
	//highlight its rectangle bounds

	gui.draw(*windowPtr);	//tell menus to draw
}



void Editor::addObject()
{
	std::string type;
	gui.popup("Enter Object Type: ", type);	//get that object type

	//check for type validity

	StringMap properties = objectAttributes[type];
	boost::property_tree::ptree objectRoot;

	auto tempObject = objMan.getPrototype(type);
	tempObject->setID(objMan.nextID());
	tempObject->setActive(false);

	idList[tempObject->getID()] = std::make_tuple(objectRoot, properties);

	gui.setMap("editorMenu", "attributeEditor", properties);	//prompt for all object attributes

	selectObject(tempObject->getID());

	std::string pathString = "Layers.Layer" + boost::lexical_cast<std::string>(currentLayer);
	objMan.addObject(tempObject, pathString);

	//ask for object type
	//get the object stuff and display it with dropdowns options in the gui
	//wait for all input to be complete
	//update object

}

void Editor::editObject()	//edits currently selected object
{
	gui.setMap("editorMenu", "attributeEditor", *objProperties);

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

		sf::Vector2f chunk;
		if (splitChunk.size() < 2)
		{
			//error -- object chunk data not detected reverting to default (0, 0)
			//revert to default
		}
		else
		{
			chunk = sf::Vector2f(boost::lexical_cast<float>(splitChunk[0]), boost::lexical_cast<float>(splitChunk[1]));
		}
		
		int layer = std::get<0>(it->second)["layer"];

		//for (int layer)
	}
}

void Editor::addResource()
{

}

void Editor::editResource(std::string& name)
{

}

void Editor::removeResource(std::string& name)
{

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

	for (int typeIt = 0; typeIt < types.size(); i++)
	{
		StringMap attrMap;
		for (int attrIt = 0; attrIt < attributes.size(); attrIt++)
		{
			attrMap[attributes[attrIt]] = "";
		}
		objectAttributes[types[typeIt]] = attrMap;
	}

	//for files in directory
	//load file name
	//while getline load attribute to that map
	//done

	//somehow get stringified object prototype names (xml format?)
}



