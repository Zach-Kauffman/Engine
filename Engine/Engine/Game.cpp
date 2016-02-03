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
						keys.push_back(i);									//add the pressed key index to the keys vector
				
					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
				{
					if (event.key.code == (sf::Keyboard::Key)(i))
					{
						keys.erase( remove( keys.begin(), keys.end(), i ), keys.end() );	//removes all released keys from the keys vector
				
					}
				}
			}
			


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
	const unsigned int layerAMT = layMan.getLayerAmount();

	boost::function<void(objects::Object&)> draw;

	for (unsigned int i = 0; i < layerAMT; i++)
	{
		draw = boost::bind(&objects::Object::draw, _1, boost::ref(*(layMan.getLayerPointer(i))));
		objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(i + 1), draw);
	}

	//objMan.getObject("Layers.Layer1.1").get()->draw(*layMan.getLayerPointer(0));
	//objMan.getObject("Layers.Layer1.2").get()->draw(*layMan.getLayerPointer(0));
	layMan.draw(*windowPtr.get());
}

void Game::update()
{
	//tmpCenter.y += 1;
	objMan.getObject("Layers.Layer1.5")->update(keys);

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
	objMan.addPrototype<objects::MovingTestObject>("MovingTestObject");
}

void Game::loadMap()
{
	XMLParser parser(mapFile);

	/*
	xmlTree<std::string> groupTree;
	groupTree.branch("map");

	auto& tags = groupTree.trees["map"].tags;
	tags["type"] = "";							//setting individual attributes to load from xml file
	tags["position.<xmlattr>.x"] = "";
	tags["position.<xmlattr>.y"] = "";
	tags["texture"] = "";

	parser.readTree<std::string>(groupTree);
	auto& output = groupTree.trees["map"].output;

	//blech hardcoded for now
	std::string type = output[0][3];
	std::string x = output[0][0];
	std::string y = output[0][1];
	std::string tex = output[0][2];

	auto tmp = objMan.getPrototype(type);
	tmp.get()->load(tex, boost::lexical_cast<int, std::string>(x), boost::lexical_cast<int, std::string>(y), recMan);
	tmp.get()->setID(objMan.nextID());
	objMan.addObject(tmp, "Layers.Layer1");
	*/

	xmlTree<boost::property_tree::ptree> groupTree;
	groupTree.branch("map");

	parser.getSubTree(groupTree);

	auto& output = groupTree.output;

	for (unsigned int i = 0; i < output[0].size(); i++)
	{
		std::string type = "";
		parser.readValue<std::string>("type", type, output[0][i]);	//read type from tree
		auto tmp = objMan.getPrototype(type);						//make object of that type
		tmp->load(output[0][i], recMan);
		tmp->setID(objMan.nextID());
		if (i == 1)
		{
			objMan.addObject(tmp, "Layers.Layer2");
		}
		else if (i == 2)
		{
			objMan.addObject(tmp, "Layers.Layer3");
		}
		else
		{
			objMan.addObject(tmp, "Layers.Layer1");
		}
		
	}

	//setting up the layer manager
	layMan.setDefaultSize((sf::Vector2f)windowPtr->getSize());	//size of the viewport
	layMan.setLayerAmount(3);
	layMan.setScrollSpeeds({ sf::Vector2f(1, 1), sf::Vector2f(.4, .7), sf::Vector2f(.1, .1) });			//this layer should scroll at the same speed as movement		
	layMan.updateWindowSize(windowPtr.get()->getSize());		//umm idk?

	tmpCenter = sf::Vector2f(500, 500);							//starting point of reference


	util::Downcaster<objects::Object> tmpDC;
	layMan.setReferencePoint(*(tmpDC.downcastMTO(objMan.getObject("Layers.Layer1.5"))->getPositionPtr()));						//make sure the layers reference the point
	//layMan.setReferencePoint(tmpCenter);
	for (int i = 0; i < 3; i++)
	{
		layMan.setScrollBounds( { 0, 0, 2000, 2000 }, i);
		layMan.setWindowCorners(sf::Vector2f(0, 0), (sf::Vector2f)windowPtr->getSize(), i);
		layMan.getLayerPointer(i)->setScrollBoundedness(true);
	}
	layMan.createAllLayers();

	
}


