#include "EntryTable.hpp"


EntryTable::EntryTable()
{
	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	
}


EntryTable::~EntryTable()
{
}


EntryTable::EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos, sf::Font * const ffont, const sf::Color& fcolor, sf::Texture* const bgTex,
	const sf::Vector2f& bgSiz, sf::Texture * const fbarTex, const double& findent)
{

	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	

	font = ffont;
	color = fcolor;
	bgTexture = bgTex;
	bgSize = bgSiz;
	barTexture = fbarTex;
	indent = findent;
	setup(xspac, yspac, csiz, pos);
}

void EntryTable::setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos)
{
	xSpacing = xspac;
	ySpacing = yspac;
	charSize = csiz;
	position = pos;
}

void EntryTable::setMap(std::map<std::string, std::string>& tableData)
{

	std::map<std::string, std::string>::iterator it;
	unsigned int i = 0;
	for(it = tableData.begin(); it != tableData.end(); it++) {
	 // iterator->first = key
		tablePairs.push_back(TablePair(font, charSize, color, bgTexture, bgSize, barTexture, sf::Vector2f(0, i*ySpacing), indent, xSpacing));
		tablePairs[i].setKeyString(it->first);
		tablePairs[i].setEntryString(it->second);
		i++;
	}

}



void EntryTable::update(InputData& inpData)
{
	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		tablePairs[i].update(inpData);

	}
}


void EntryTable::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;

	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		tablePairs[i].draw(window, position);
	}

	position -= drawPos;
}