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
	T readValue(const std::string& key)
	{
		return tree.get<T>(key);
	}

	template<class T>
	std::vector<T> readVector(const std::vector<std::string> &keyNames)
	{
		std::vector<T> toReturn;
		for (int i = 0; i < keyNames.size(); i++)
		{
			toReturn.push_back(tree.get<T>(keyNames[i]));
		}
		return toReturn;
	}

private:
	boost::property_tree::ptree tree;
	std::string filePath;
	src::severity_logger<severity_level> logger;
};

