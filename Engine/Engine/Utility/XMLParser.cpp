#include "XMLParser.hpp"

//public functions

XMLParser::XMLParser(){}	//default constructor
	
XMLParser::~XMLParser(){}	//defautl destructor

XMLParser::XMLParser(const std::string& XMLPath)
{
	setFilePath(XMLPath);
	init();
} 

void XMLParser::init()
{

}

void XMLParser::setFilePath(const std::string& XMLPath)
{
	if (XMLPath != "")	//if there is no string input, only reload the file
	{
		filePath = XMLPath;
		BOOST_LOG_SEV(logger, DEBUG) << "XMLParser path set to " << filePath;
	}

	try	//attempt to load from file
	{
		boost::property_tree::read_xml(filePath.c_str(), tree);
	}
	catch (boost::property_tree::ini_parser::ini_parser_error E)	//catch error and exit
	{
		BOOST_LOG_SEV(logger, FATAL) << "FAILED TO LOAD XML FILE FROM PATH " << filePath << ": Exiting... ";
		exit(0); //exit with error
	}
}

//private functions

