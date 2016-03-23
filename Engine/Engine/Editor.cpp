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

//update needs to allow for GUI and object selection
void Editor::editorUpdate()
{
	//run selection check for (all???) objects or at least the current layer

	//update gui
}

//draw needs to draw GUI
void Editor::editorDraw()
{
	//find object with id of currently selected
	//highlight its rectangle bounds

	//draw gui
}

void Editor::addObject()
{
	std::string type = GUI.popup("Enter Object Type: ");	//get that object type

	//check for type validity

	StringMap properties = objectAttributes[type];
	boost::property_tree::ptree objectRoot;

	auto tempObject = objMan.getPrototype(type);
	tempObject->setID(objMan.nextID());
	tempObject->setActive(false);

	idList[tempObject->getID()] = std::make_tuple(objectRoot, properties);

	GUI.prompt(properties);	//prompt for all object attributes

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
	GUI.prompt(objProperties);

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
	for (it = objProperties.begin(); it != objProperties.end(); it++)	//iterate through values and store them in property tree
	{
		newXml.put(it->first, it->second);
	}

	objXml = newXml;

	auto tmp = objMan.getObject(objID);	
	tmp->load(objXml, recMan);
	tmp->setActive(true);
	//calculate chunk and add here
}

void Editor::selectObject(const int& ID)
{
	SelectionData& toSelect = idList[ID];

	objXml = std::get<0>(toSelect);
	objProperties = std::get<1>(toSelect);
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

		for (int layer)
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

void Editor::loadAttributes(std::string& path) //loads object attributes from set of files....??
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
			attrMap[]
		}
	}

	//for files in directory
	//load file name
	//while getline load attribute to that map
	//done

	//somehow get stringified object prototype names (xml format?)
}



