#pragma once

//boost includes
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

//project includes
#include "Logger.hpp"
#include "Utilities.hpp"

//standard includes
#include <string.h>
#include <vector>

class XMLParser
{
public:
	XMLParser();
	~XMLParser();
	XMLParser(const std::string& XMLPath);			//just call setFilePath()

	void init();
	void setFilePath(const std::string& XMLPath);	//fills property tree with xml file data
	
private:
	boost::property_tree::ptree tree;				//boost class to hand xml parsing
	std::string filePath;							//file to read from
	src::severity_logger<severity_level> logger;	//logging for parser object
};
