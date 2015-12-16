#include "INIParser.hpp"


INIParser::INIParser(){ init(); }			//default constructor

INIParser::~INIParser(){}					//default destructor

INIParser::INIParser(const std::string& INIPath)	//overloaded constructor with filepath
{
	setFilePath(INIPath);
	init();
}

void INIParser::init()
{
	setFilePath("");
	logger = logger::getSLogger();
	BOOST_LOG_SEV(logger, INFO) << "INIParser Initialization Completed";
}

void INIParser::setFilePath(const std::string& INIPath)
{
	if (INIPath != "")	//if there is no string input, only reload the file
	{
		filePath = INIPath;
		BOOST_LOG_SEV(logger, DEBUG) << "INIParser path set to " << filePath;
	}
	
	try	//attempt to load from file
	{
		boost::property_tree::read_ini(filePath.c_str(), tree);
	}
	catch (boost::property_tree::ini_parser::ini_parser_error E)	//catch error and exit
	{
		BOOST_LOG_SEV(logger, FATAL) << "FAILED TO LOAD INI FILE FROM PATH " << filePath << ": Exiting... ";
		exit(0); //exit with error
	}
	
}

