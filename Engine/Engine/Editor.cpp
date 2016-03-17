#include "Editor.hpp"

Editor::Editor()
{

}

Editor::~Editor()
{

}

//update needs to allow for GUI and object selection
void Editor::editorUpdate()
{

}

//draw needs to draw GUI
void Editor::editorDraw()
{

}

void Editor::addObject()
{
	std::string type = GUI.prompt<std::string>("Enter Object Type: ");	//get that object type

	//check for type validity

	std::map<std::string, std::string> properties = GUI.prompt(objectAttributes[type]);	//prompt for all object attributes

	boost::property_tree::ptree objectRoot;

	std::map<std::string, std::string>::iterator it;
	for (it = properties.begin(); it != properties.end(); it++)	//iterate through values and store them in property tree
	{
		objectRoot.put(it->first, it->second);
	}

	auto tmp = objMan.getPrototype(type);
	tmp->load(objectRoot, recMan);
	tmp->setID(objMan.nextID());

	
	std::string pathString = "Layers.Layer" + GUI.currentLayer();

	//calculate chunk and add here

	objMan.addObject(tmp, pathString);
	//ask for object type
	//get the object stuff and display it with dropdowns options in the gui
	//actually add the object to game with button press
		//construct object property tree
		//create object prototype and load properties
		//display object
		//save tree in temporary location (not in file)(hard to delete there)
	//save xml
}

void Editor::editObject(std::string& type)
{
	//find object xml by id in storage
	//redisplays option with current selection for editing
	//resaves and updates
}

void Editor::removeObject(std::string& ID)
{
	//deletes object xml and clears id from storage
	//
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

void Editor::loadObjectAttributes(std::string& path) //loads object attributes from set of files....??
{
	//somehow get stringified object prototype names (xml format?)
}

