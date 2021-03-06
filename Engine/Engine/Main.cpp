#include "Defines.hpp"	//global #defines

#ifndef RUN_TESTS


#include "Logger.hpp"
#include "INIParser.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Utilities.hpp"
#include <boost/core/null_deleter.hpp>

void logging_function()
{
	//BOOST_LOG_NAMED_SCOPE("INI_Reader_Testing");											<<--- adds specified namespace to logs in all nested scopes
	//BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer()));							<<--- adds timer to logs in all nested scopes
	//severity_logger.add_attribute("Tag", attrs::constant<std::string>("<yourstring>"));	<<--- adds tag attribute in brackets ex. [<yourstring>]

	INIParser reader("config.ini");

	int one =3, two = 1, three = 3;
	reader.setSection("Beans");
	std::map<std::string, int*> variables;
	variables["Ehhh"] = &one;
	variables["Meh"] = &two;
	variables["Heh"] = &three;
	std::string testing = "test";
	reader.readValue<std::string>("string", testing);
	reader.readMap<int>(variables);

	reader.setSection("");
	reader.writeValue<int>("Eugene.cookies", 7);	//Adds header called "eugene" with an attribute called "cookies" which has a value of 7

	reader.writeMap<int>(variables);				//writeMap() test
	reader.readMap<int>(variables);



	auto slg = logger::getSLogger();
	slg.add_attribute("Scope", attrs::named_scope());
	int cookies = 1;
	reader.readValue<int>("Eugene.cookies", cookies);
	//BOOST_LOG_SEV(slg, DEBUG) << "This is the first value as a string. " << reader.readValue<std::string>("Beans.Smoky");
	BOOST_LOG_SEV(slg, ERROR) << "Array values as int. " << one << " + " << two;
	BOOST_LOG_SEV(slg, INFO) << "This is a string: " << testing;
	BOOST_LOG_SEV(slg, ERROR) << "Eugene's cookies: " << cookies;

	

}



int main(int, char*[])
{

	logger::init();
	logger::setSeverityLevel(DEBUG);
	//logging_function();
	auto slg = logger::getSLogger();

	typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
	boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

	// Add a stream to write log to
	sink->locked_backend()->add_stream(
		boost::make_shared< std::ofstream >("sample.log"));

	// Register the sink in the logging core
	logging::core::get()->add_sink(sink);

#ifdef LOG_CONSOLE
	boost::shared_ptr< std::ostream > stream(&std::clog, boost::null_deleter());
	sink->locked_backend()->add_stream(stream);
#endif

	util::splitStrAtSubstr("One.Two.Three", ".");
	util::reverseString("aaaaa");
	std::string directoryToResources = boost::filesystem::current_path().string() + "\\Resources\\";
	ResourceManager testRM;
	testRM.addFilesResourceGroupFromDirectory(directoryToResources + "TestResources");


	for (int i = 0; i < 40; i++){
		testRM.loadFile(directoryToResources + "TestResources\\ModernArtBlue.png", "ModernArtBlueTest");
	}


	BOOST_LOG_SEV(slg, DEBUG) << "Exiting soon";

	std::cin.ignore();
	
	return 0;
}

#endif


#ifdef RUN_TESTS


#include "Logger.hpp"
#include "UnitTester.hpp"


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
