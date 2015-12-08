#include "INIReader.h"


INIReader::INIReader(){ init(); }			//default constructor

INIReader::~INIReader(){}					//default destructor

INIReader::INIReader(const std::string& INIPath)	//overloaded constructor with filepath
{
	setFilePath(INIPath);
	init();
}

void INIReader::init()
{
	setFilePath("");
	logger = getSLogger();
}

void INIReader::setFilePath(const std::string& INIPath)
{
	if (INIPath != "")	//if there is no string input, only reload the file
	{
		filePath = INIPath;
	}
	
	try
	{
		boost::property_tree::read_ini(filePath.c_str(), tree);
	}
	catch (boost::property_tree::ini_parser::ini_parser_error E)
	{
		BOOST_LOG_SEV(logger, FATAL) << "FAILED TO LOAD INI FILE FROM PATH " << filePath << ": Exiting... ";
		exit(0); //exit with error
	}
	
}

