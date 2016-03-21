#pragma once
#include "TablePair.hpp"

class EntryTable
{
public:
	EntryTable();
	EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);
	~EntryTable();

	void setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);

	void setMap(std::map<std::string, std::string>& fmap);
	void createTable(sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex);


	void update(const char& typedChar, MouseData& mdata);
	void draw(const sf::Vector2f& drawpos, sf::RenderWindow& window);
private:

	
	std::vector<TablePair> tablePairs;
	std::map<std::string, std::string>* strMap;
	std::vector<std::string> recordstrs;

	sf::Vector2f position;
	double xSpacing;
	double ySpacing;
	unsigned int charSize;

};

