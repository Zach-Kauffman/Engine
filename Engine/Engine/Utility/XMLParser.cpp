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
	subTree = tree;
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
		read_xml(filePath.c_str(), tree);
	}
	catch (boost::property_tree::xml_parser::xml_parser_error E)	//catch error and exit
	{
		BOOST_LOG_SEV(logger, FATAL) << "FAILED TO LOAD XML FILE FROM PATH " << filePath << ": Exiting... ";
		exit(0); //exit with error
	}
}

void XMLParser::writeFile()
{
	write_xml(filePath, tree);
}

void XMLParser::writeFile(const std::string& XMLPath)
{
	write_xml(XMLPath, tree);
}

void XMLParser::setWorkingPath(const std::string& newPath)
{
	workingPath = newPath;
	subTree = getSubTree(newPath);
}

void XMLParser::getSubTree(xmlTree<boost::property_tree::ptree>& data, boost::property_tree::ptree& currentTree)
{

	//no tags to read, output will be property trees

	std::map<std::string, xmlTree<boost::property_tree::ptree>>::iterator treeIt;


	for (treeIt = data.trees.begin(); treeIt != data.trees.end(); treeIt++)	//iterate through all children
	{
		std::vector<boost::property_tree::ptree> output;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, subTree.get_child(treeIt->first))
		{
			output.push_back(v.second);
			getSubTree(treeIt->second, v.second);
		}
		data.output.push_back(output);
	}

}

void XMLParser::getSubTree(xmlTree<boost::property_tree::ptree>& data)
{
	getSubTree(data, subTree);	//calls with default argument as the current subtree
}

boost::property_tree::ptree XMLParser::getSubTree(const std::string& path)		//gets specified subtree from tree and stores it for later use.
{
	return tree.get_child(path);
}

boost::property_tree::ptree XMLParser::getSubTree()
{
	return subTree;
}
//private functions

std::string XMLParser::assemblePath(const std::string& path)
{
	return workingPath + "." + path;
}

