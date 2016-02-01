#include "Defines.hpp"	//global #defines

#ifndef RUN_TESTS

#include "Utility/Logger.hpp"
#include "Utility/INIParser.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Utility/Utilities.hpp"
#include "Objects/ObjectManager.hpp"
#include "TestObject.hpp"
#include "Objects/Object.hpp"
#include "Game.hpp"
#include "Utility\XMLParser.hpp"
#include <iostream>

int main(int, char*[])
{

	logger::init();
	logger::setSeverityLevel(DEBUG);
	//logging_function();
	auto slg = logger::getSLogger();

	/*
	objects::ObjectManager OhMan;
	util::Downcaster<objects::Object> dc;

	boost::shared_ptr<objects::Object> tmp(new objects::TestObject);
	tmp->setID(OhMan.nextID());

	
	OhMan.addObject(tmp, "Test.Update");

	auto testObject = dc.downcast(OhMan.getObject("Test.Update.1"));
	
	for (unsigned int i = 0; i < 100; i++)
	{
		testObject->update();
		BOOST_LOG_SEV(slg, INFO) << testObject->getCounter();
	}
	*/

	XMLParser parser("test.xml");
	int num = 0;
	parser.readValue<int>("number", num);
	std::cout << num << std::endl;
	BOOST_LOG_SEV(slg, INFO) << "The number from XML is: " << num;

	Game theGame;
	theGame.initialize("gameConfig.ini", "resources.xml", "objects.xml", "map.xml", "save.xml", 0);
	theGame.begin();	//starts SFML main loop

	BOOST_LOG_SEV(slg, DEBUG) << "Exiting soon";
	return 0;
}

#endif


#ifdef RUN_TESTS


#include "Logger.hpp"
#include "UnitTester.hpp"
#include "Utilities.hpp"

#define TEST_ALL

int main(int, char*[])
{
	logger::init();
	logger::setSeverityLevel(INFO);
	auto slg = logger::getSLogger();

	BOOST_LOG_SEV(slg, INFO) << "Starting Unit Tests...";

	testing::UnitTester testObject;
	testObject.runTests();

	BOOST_LOG_SEV(slg, INFO) << "Unit test completed...";
}

#endif
