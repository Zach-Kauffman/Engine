#include "Game.hpp"



//PUBLIC FUNCTIONS

Game::Game(){}

Game::~Game(){}

void Game::initialize(const std::string& cfgFile, const std::string& resFile, const std::string& objFile, const std::string& mpFile, const std::string& save, const bool& doLoadScreen)
{
	configFile = cfgFile; resourceFile = resFile; objectFile = objFile; mapFile = mpFile; saveFile = save;
	loadGameConfig(configFile);

	windowPtr = boost::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(renderSize.x, renderSize.y), windowName));
	
	if (maxFPS > 0)
	{
		windowPtr.get()->setFramerateLimit(maxFPS);	//initial FPS limit
	}
	
	loadResources();	//loads texture sounds, etc
		
	loadObjects();		//creates object prototypes
	
	loadMap();			//displays correct objects

	//thats all for now folks

}

void Game::begin()
{
	//sfml main loop
	sf::RenderWindow& window = *windowPtr;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		update();
		draw();

		window.display();
	}
}


//PRIVATE FUNCTIONS

void Game::draw()
{
	for (int i = 0; i < numLayers; i++)	//draw objects to all layers
	{
		boost::function<void(objects::Object&)> draw = boost::bind(&objects::Object::draw, _1, boost::ref(*layMan.getLayerPointer(i)));
		objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(i), draw);
	}
	
	layMan.draw(*windowPtr.get());	//actually draw layers to window
}

void Game::update()
{
	
	//for each layer
		//get draw bounds for layer
		//remove out of bound objects
		//add new in-bound objects
}

void Game::loadGameConfig(const std::string& configFile)
{
	INIParser parser(configFile);
	windowName = "Squirrel Game";
	renderSize = sf::Vector2i(960, 540);
	maxFPS = 0;

	parser.setSection("Render_Options");
	parser.readValue<std::string>("Window_Name", windowName);
	parser.readValue<int>("Res_X", renderSize.x); parser.readValue<int>("Res_Y", renderSize.y);
	parser.readValue<int>("FPS_Cap", maxFPS);

}

void Game::loadResources()
{
	XMLParser parser(resourceFile);
	
	xmlTree<std::string> groupTree;
	groupTree.branch("resources");

	groupTree.trees["resources"].tags["path"] = "";	//path to resource
	groupTree.trees["resources"].tags["name"] = "";	//storage name of resource

	parser.readTree<std::string>(groupTree);		//read data from file and place in output vector

	auto &output = groupTree.trees["resources"].output;
	for (unsigned int ii = 0; ii < output.size(); ii++)
	{
		recMan.loadFile(output[ii][1], output[ii][0]);	//load each resource
	}

}

void Game::loadObjects()
{
	objMan.addPrototype<objects::TestObject>("TestObject");
}

void Game::loadMap()
{
	XMLParser parser(mapFile);

	xmlTree<boost::property_tree::ptree> groupTree;

	groupTree.trees["map"];
	groupTree.tags["layer"];
	groupTree.trees["map"].trees["object"];
	groupTree.trees["map"].tags["object"];

	parser.getSubTree(groupTree);

	auto& layers = groupTree.output;
	auto& objects = groupTree.output[0][0].get_child("object");

	for (unsigned int i = 0; i < layers[0].size(); i++)	//for each layer
	{
		//reading layer data
		std::string layerNumber = "1";	//default is 1
		parser.readValue<std::string>("<xmlattr>.z", layerNumber, layers[0][i]);

		//xmlTree<boost::property_tree::ptree> objectTree;
		//for (unsigned int objectIt = 0; objectIt < objects.size(); objectIt++)
		//{
			std::string type = "";
			parser.readValue<std::string>("type", type, objects);	//read type from tree
			auto tmp = objMan.getPrototype(type);						//make object of that type
			tmp->load(objects, recMan);
			tmp->setID(objMan.nextID());
			objMan.addObject(tmp, "Layers.Layer" + layerNumber);
		//}*/
	}

	numLayers = layers[0].size();

	//setting up the layer manager
	layMan.setDefaultSize((sf::Vector2f)windowPtr->getSize());	//size of the viewport

	for (int i = 1; i <= numLayers; i++)
	{
		layMan.addLayer();											//creates a single layer
		layMan.setScrollSpeeds(sf::Vector2f(1/i, 1/i), i-1);		//decreasing movement ratio the further the layer
	}
	layMan.updateWindowSize(windowPtr.get()->getSize());		//umm idk?
	tmpCenter = sf::Vector2f(500, 500);							//starting point of reference
	layMan.setReferencePoint(tmpCenter);						//make sure the layers reference the point

}


