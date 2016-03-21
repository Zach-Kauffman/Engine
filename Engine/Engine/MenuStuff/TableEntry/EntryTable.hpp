#pragma once
#include "TablePair.hpp"

class EntryTable : MenuElement
{
public:
	EntryTable();
	EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);
	~EntryTable();

	void setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);

	void setMap(std::map<std::string, std::string>& fmap);
	void createTable(	sf::Font * const ffont, const sf::Color &fcolor, sf::Texture* const bgTex,
						const sf::Vector2f& bgSiz, sf::Texture * const barTex, const double& indent
						);

	void update() {};
	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);
	void draw(sf::RenderWindow& window, sf::Vector2f drawPos);
	void resetMD() {};
private:

	
	std::vector<TablePair> tablePairs;
	std::map<std::string, std::string>* strMap;
	std::vector<std::string> recordstrs;

	double xSpacing;
	double ySpacing;
	unsigned int charSize;

};

