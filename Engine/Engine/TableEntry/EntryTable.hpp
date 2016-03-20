#pragma once
#include "TablePair.hpp"

class EntryTable
{
public:
	EntryTable();
	EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);
	~EntryTable();

	void setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);

	void setMapKeys(const std::vector<std::string>& keys, sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex);


	void update(const std::string& curstr, MouseData& mdata);
	void draw(const sf::Vector2f& drawpos, sf::RenderWindow& window);
private:

	
	std::vector<TablePair> tablePairs;
	std::map<std::string, std::string> strMap;

	sf::Vector2f position;
	double xSpacing;
	double ySpacing;
	unsigned int charSize;

};

