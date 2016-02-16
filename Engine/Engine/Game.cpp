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
	numLayers = layMan.getLayerAmount();

	for (int i = 0; i < numLayers; i++)	//draw objects to all layers
	{
		boost::function<void(objects::Object&)> draw = boost::bind(&objects::Object::draw, _1, boost::ref(*layMan.getLayerPtr(i)));
		objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(i), draw);
	}
	
	layMan.draw(*windowPtr.get());	//actually draw layers to window

}

void Game::update()
{
	doChunks();
	objMan.getObject("Layers.Layer0.1")->update(keys);

	//for each layer
		//get draw bounds for layer
		//remove out of bound objects
		//add new in-bound objects
}

void Game::doChunks()
{
	for (unsigned int layIt = 0; layIt < numLayers; layIt++)	//for each layer
	{
		//reading layer data
		sf::Vector2f TLC = layMan.getLayerPtr(layIt)->getWindowCorners().first;
		sf::Vector2f BRC = layMan.getLayerPtr(layIt)->getWindowCorners().second;

		TLC = sf::Vector2f(std::floor(TLC.x/chunkSize.x), std::floor(TLC.y/chunkSize.y));
		BRC = sf::Vector2f(std::ceil(BRC.x / chunkSize.x), std::ceil(BRC.y / chunkSize.y));


	}
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

	parser.readValue<int>("ChunkSize_X", chunkSize.x);
	parser.readValue<int>("ChunkSize_Y", chunkSize.y);
	if (!chunkSize.y || chunkSize.y == 0){ chunkSize.y = chunkSize.x; }

	parser.setSection("Game_Options");

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

	mapData.trees["map"];
	mapData.tags["layer"];
	mapData.trees["map"].trees[""];
	mapData.trees["map"].tags["object"];


	parser.getSubTree(mapData);

	auto& layers = mapData.output;
	auto& objects = mapData.trees["map"].output;

	layMan.setLayerAmount(layers[0].size());
	numLayers = layMan.getLayerAmount();

	for (unsigned int layIt = 0; layIt < layers[0].size(); layIt++)	//for each layer
	{
		//reading layer data
		

		for (int objIt = 0; objIt < objects[layIt].size(); objIt++)		//for every object
		{
			//making a new object
			std::string type = "";
			parser.readValue<std::string>("type", type, objects[layIt][objIt]);	//read type from tree
			auto tmp = objMan.getPrototype(type);						//make object of that type
			tmp->load(objects[layIt][objIt], recMan);
			tmp->setID(objMan.nextID());
			objMan.addObject(tmp, "Layers.Layer" + layIt);
		}


	}


	//setting up the layer manager

	tmpCenter = sf::Vector2f(500, 500);							//starting point of reference


	util::Downcaster<objects::Object> tmpDC;
	layMan.setReferencePoint(*(tmpDC.downcastMTO(objMan.getObject("Layers.Layer0.1"))->getPositionPtr()));						//make sure the layers reference the point
	//layMan.setReferencePoint(tmpCenter);
	for (int i = 0; i < numLayers; i++)
	{
		std::string layerNumber = "1";	//default is 1
		parser.readValue<std::string>("<xmlattr>.z", layerNumber, layers[0][numLayers]);

		sf::Vector2f scrollSpeed = sf::Vector2f(0, 0);
		parser.readValue<float>("<xmlattr>.scrollx", scrollSpeed.x, layers[0][numLayers]);
		parser.readValue<float>("<xmlattr>.scrolly", scrollSpeed.y, layers[0][numLayers]);
		layMan.setScrollSpeed(scrollSpeed, numLayers);

		sf::Vector2f bounds = sf::Vector2f(0, 0);	//default to not moving
		parser.readValue<float>("<xmlattr>.boundx", bounds.x, layers[0][numLayers]);
		parser.readValue<float>("<xmlattr>.boundy", bounds.y, layers[0][numLayers]);

		layMan.setScrollBounds({ 0, 0, bounds.x, bounds.y}, i);
		layMan.setCorners(sf::Vector2f(0, 0), (sf::Vector2f)windowPtr->getSize(), i);
		layMan.getLayerPtr(i)->setScrollBoundedness(true);

	}
	
	layMan.createLayers();
	layMan.setDependentLocking(true, 0);

	
	
}


