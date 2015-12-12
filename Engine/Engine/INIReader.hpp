#pragma once

#include "Logger.h"
#include <boost\property_tree\ini_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <string.h>
#include <vector>

class INIReader
{
public:
	INIReader();
	~INIReader();
	INIReader(const std::string& INIPath);

	void init();
	void setFilePath(const std::string& INIPath);

	template<class T>
	T readValue(const std::string& key)	//takes a string and return its value loaded from INI
	{
		//tree.get would throw ptree_bad_path (ptree_error) on nonexistent value
		boost::optional<T> op = tree.get_optional<T>(key); //returns uninitialized boost::optional object if value != exist

		if (op)
		{
			return *op;
		}
		else
		{
			BOOST_LOG_SEV(logger, INFO) << "Value \"" << key << "\" not loaded from INI file " << filePath;

			return NULL;	//return NULL value
		}
	}

	template<class T>
	std::vector<T> readVector(const std::vector<std::string> &keyNames)	//reads vector of strings and returns vector of matching values as loaded from ini value
	{
		std::vector<T> toReturn;
		for (int i = 0; i < keyNames.size(); i++)
		{
			toReturn.push_back(readValue<T>(keyNames[i])); //get and push back value
		}
		return toReturn;
	}

	template<class T>
	void readWriteMap(std::map < std::string, T*>& valMap)
	{
		typedef std::map<std::string, T*>::iterator it;		//construct iterator for map object
		for (it i= valMap.begin(); i != valMap.end(); i++)	//iterate through map
		{
			*valMap[i->first] = readValue<T>(i->first);		//read value and place it in the map
		}
	}

private:
	boost::property_tree::ptree tree;				//boost class that handles ini parsing
	std::string filePath;							//file to read from
	src::severity_logger<severity_level> logger;	//logger to handle debuging and errors
};

