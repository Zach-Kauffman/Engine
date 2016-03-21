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
	loadEntryTable();
		
	//loadObjects();		//creates object prototypes
	
	//loadMap();			//displays correct objects

	//thats all for now folks

	textDataStr = "";
	textDataChr = 0;
	
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
		draw();

		window.display();

		textDataChr = 0;
		keyData.frameUpdate();
		mouseData.frameUpdate();
	}


}


//PRIVATE FUNCTIONS

void Game::draw()
{
	gui.draw(sf::Vector2f(0, 0), *windowPtr);
	//layMan.setupDraw();										//need to setup draw before objects are drawn


	//numLayers = layMan.getLayerAmount();

	//for (int i = 0; i < numLayers; i++)	//draw objects to all layers
	//{
	//	boost::function<void(objects::Object&)> draw = boost::bind(&objects::Object::draw, _1, boost::ref(*layMan.getLayerPtr(i)));
	//	objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(i), draw);
	//}
	//
	//layMan.draw(*windowPtr.get());	//actually draw layers to window

}

void Game::update()
{

	gui.update(textDataChr, mouseData);
	std::cout << testMap["Cat"] << ", " << testMap["Ani"] << std::endl;
	//objMan.getObject("Layers.Layer0.1")->update(keys);

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

	xmlTree<boost::property_tree::ptree> groupTree;

	groupTree.trees["map"];
	groupTree.tags["layer"];
	groupTree.trees["map"].trees[""];
	groupTree.trees["map"].tags["object"];


	parser.getSubTree(groupTree);

	auto& layers = groupTree.output;
	auto& objects = groupTree.trees["map"].output;

	layMan.setLayerAmount(layers[0].size());
	numLayers = layMan.getLayerAmount();

	for (unsigned int layIt = 0; layIt < layers[0].size(); layIt++)	//for each layer
	{
		//reading layer data
		std::string layerNumber = "1";	//default is 1
		parser.readValue<std::string>("<xmlattr>.z", layerNumber, layers[0][layIt]);

		sf::Vector2f scrollSpeed = sf::Vector2f(0, 0);
		parser.readValue<float>("<xmlattr>.scrollx", scrollSpeed.x, layers[0][layIt]);
		parser.readValue<float>("<xmlattr>.scrolly", scrollSpeed.y, layers[0][layIt]);
		layMan.setScrollSpeed(scrollSpeed, layIt);

		for (int objIt = 0; objIt < objects[layIt].size(); objIt++)		//for every object
		{
			//making a new object
			std::string type = "";
			parser.readValue<std::string>("type", type, objects[layIt][objIt]);	//read type from tree
			auto tmp = objMan.getPrototype(type);						//make object of that type
			tmp->load(objects[layIt][objIt], recMan);
			tmp->setID(objMan.nextID());
			objMan.addObject(tmp, "Layers.Layer" + layerNumber);
		}


	}


	//setting up the layer manager
//	layMan.setDefaultSize((sf::Vector2f)windowPtr->getSize());	//size of the viewport

//	layMan.setScrollSpeed({ sf::Vector2f(1, 1), sf::Vector2f(.4, .7), sf::Vector2f(.1, .1) });			//this layer should scroll at the same speed as movement		
//	layMan.updateWindowSize(windowPtr.get()->getSize());		//umm idk?

	tmpCenter = sf::Vector2f(500, 500);							//starting point of reference


	util::Downcaster<objects::Object> tmpDC;
	layMan.setReferencePoint(*(tmpDC.downcastMTO(objMan.getObject("Layers.Layer0.1"))->getPositionPtr()));						//make sure the layers reference the point
	//layMan.setReferencePoint(tmpCenter);
	for (int i = 0; i < numLayers; i++)
	{
		layMan.setScrollBounds({ 0, 0, 8000, 8000 }, i);
		layMan.setCorners(sf::Vector2f(0, 0), (sf::Vector2f)windowPtr->getSize(), i);
		layMan.getLayerPtr(i)->setScrollBoundedness(true);
	}
	
	layMan.createLayers();
	layMan.setDependentLocking(true, 0);

	
	
}


void Game::loadEntryTable()
{
	
	testMap["Cat"] = "";
	testMap["Dog"] = "";
	testMap["Bun"] = "";
	testMap["Ani"] = "";

	gui.setup(200, 50, 30, sf::Vector2f(100, 100));
	gui.setMap(testMap);
	gui.createTable(recMan.getFontPointerByName("times"), recMan.getTexturePointerByName("textbar"), recMan.getTexturePointerByName("guiBG"));
}