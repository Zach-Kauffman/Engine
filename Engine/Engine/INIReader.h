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
		return tree.get<T>(key);
	}

	template<class T>
	std::vector<T> readVector(const std::vector<std::string> &keyNames)	//reads vector of strings and returns vector of matching values as loaded from ini value
	{
		std::vector<T> toReturn;
		for (int i = 0; i < keyNames.size(); i++)
		{
			toReturn.push_back(tree.get<T>(keyNames[i]));
		}
		return toReturn;
	}

private:
	boost::property_tree::ptree tree;				//boost class that handles ini parsing
	std::string filePath;							//file to read from
	src::severity_logger<severity_level> logger;	//logger to handle debuging and errors
};

