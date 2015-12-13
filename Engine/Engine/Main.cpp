#include "Logger.h"
#include "INIReader.h"
#include "ResourceManager/ResourceManager.h"


void logging_function()
{
	//BOOST_LOG_NAMED_SCOPE("INI_Reader_Testing");											<<--- adds specified namespace to logs in all nested scopes
	//BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer()));							<<--- adds timer to logs in all nested scopes
	//severity_logger.add_attribute("Tag", attrs::constant<std::string>("<yourstring>"));	<<--- adds tag attribute in brackets ex. [<yourstring>]

	INIReader reader("config.ini");
	
	int one, two, three;
	std::map<std::string, int*> variables;
	variables["Beans.Ehhh"] = &one;
	variables["Beans.Meh"] = &two;
	variables["Beans.Heh"] = &three;

	
	
	reader.readWriteMap<int>(variables);
	auto slg = logger::getSLogger();
	slg.add_attribute("Scope", attrs::named_scope());
	BOOST_LOG_SEV(slg, DEBUG) << "This is the first value as a string. " << reader.readValue<std::string>("Beans.Smoky");
	BOOST_LOG_SEV(slg, ERROR) << "Array values as int. " << one << " + " << two;

	BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer());

	BOOST_LOG_SEV(slg, INFO) << "Starting to time nested functions";

	BOOST_LOG_SEV(slg, INFO) << "Stopping to time nested functions";

	BOOST_LOG_SEV(slg, INFO) << "Here goes the tagged record";
}

// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
	static const char* strings[] =
	{
		"debug",
		"info",
		"warning",
		"error",
		"fatal"
	};

	if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
		strm << strings[level];
	else
		strm << static_cast< int >(level);

	return strm;
}

int main(int, char*[])
{

	logger::init();
	logger::setSeverityLevel(DEBUG);
	logging_function();
	auto slg = logger::getSLogger();
	


	std::string directoryToResources = "C:\\Users\\Riley\\Documents\\Visual Studio 2013\\Projects\\Engine\\Engine\\Engine\\Resources\\";
	ResourceManager testRM;
	testRM.addFilesFromDirectory(directoryToResources + "TestPngs");



	BOOST_LOG_SEV(slg, DEBUG) << "Exiting soon";
	while (true){}
	return 0;
}