#include <cstddef>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include "Logger.h"
#include "INIReader.h"


void logging_function()
{
	//BOOST_LOG_NAMED_SCOPE("INI_Reader_Testing");
	INIReader reader("config.ini");
	
	std::vector<std::string> variables;
	variables.push_back("Beans.Ehhh");
	variables.push_back("Beans.Meh");
	variables.push_back("Beans.Heh");
	std::vector<int> output = reader.readVector<int>(variables);
	auto slg = logger::getSLogger();
	slg.add_attribute("Scope", attrs::constant<std::string>("INITESTING"));
	BOOST_LOG_SEV(slg, DEBUG) << "This is the first value as a string. " << reader.readValue<std::string>("Beans.Smoky");
	BOOST_LOG_SEV(slg, ERROR) << "Array values as int. " << output[0] << " + " << output[1];
	BOOST_LOG_SEV(slg, WARNING) << "Everything crumbles, shoot me now!";
	BOOST_LOG_SEV(slg, INFO) << "2 + 2 = 4!";
	BOOST_LOG_SEV(slg, FATAL) << "Insert fatal error here";

	BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer());

	BOOST_LOG_SEV(slg, INFO) << "Starting to time nested functions";

	BOOST_LOG_SEV(slg, INFO) << "Stopping to time nested functions";

	slg.add_attribute("Tag", attrs::constant< std::string >("My tag value"));

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

	//while (true){}
	return 0;
}