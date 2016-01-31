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
	objMan.getObject("Layers.Layer1.1").get()->draw(*layMan.getLayerPointer(0));
	layMan.draw(*windowPtr.get());
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
	//recMan.addEmptyResourceGroup("objects");

	XMLParser parser(resourceFile);
	
	xmlTree<std::string> groupTree;
	groupTree.branch("resources");

	groupTree.trees["resources"].tags["path"] = "";	//path to resource
	groupTree.trees["resources"].tags["name"] = "";	//storage name of resource


	//parser.setWorkingPath("resources");

	parser.readTree<std::string>(groupTree);

	auto &output = groupTree.trees["resources"].output;
	for (unsigned int ii = 0; ii < output.size(); ii++)
	{
		recMan.loadFile(output[ii][1], output[ii][0]);
	}

	
	//load basic game resources
}

void Game::loadObjects()
{
	objMan.addPrototype<objects::TestObject>("TestObject");
}

void Game::loadMap()
{
	XMLParser parser(mapFile);

	xmlTree<std::string> groupTree;
	groupTree.branch("map");

	auto& tags = groupTree.trees["map"].tags;
	tags["type"] = "";
	tags["position.<xmlattr>.x"] = "";
	tags["position.<xmlattr>.y"] = "";
	tags["texture"] = "";

	parser.readTree<std::string>(groupTree);
	auto& output = groupTree.trees["map"].output;

	std::string type = output[0][3];
	std::string x = output[0][0];
	std::string y = output[0][1];
	std::string tex = output[0][2];

	//for (unsigned int ii = 0; ii < output.size(); ii++)
	//{
		auto tmp = objMan.getPrototype(type);
		tmp.get()->load(tex, boost::lexical_cast<int, std::string>(x), boost::lexical_cast<int, std::string>(y), recMan);
		tmp.get()->setID(objMan.nextID());
		objMan.addObject(tmp, "Layers.Layer1");
	//}
	layMan.setDefaultSize((sf::Vector2f)windowPtr->getSize());
	layMan.addLayer();
	layMan.setScrollSpeeds(sf::Vector2f(1, 1), 0);
	layMan.getLayerPointer(0);
	layMan.updateWindowSize(windowPtr.get()->getSize());
	tmpCenter = sf::Vector2f(500, 500);
	layMan.setReferencePoint(tmpCenter);

}


