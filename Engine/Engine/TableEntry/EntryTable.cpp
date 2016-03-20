#include "EntryTable.hpp"


EntryTable::EntryTable()
{
}


EntryTable::~EntryTable()
{
}


EntryTable::EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos)
{
	setup(xspac, yspac, csiz, pos);
}

void EntryTable::setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos)
{
	xSpacing = xspac;
	ySpacing = yspac;
	charSize = csiz;
	position = pos;
}

void EntryTable::setMapKeys(const std::vector<std::string>& keys, sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex)
{
	for (unsigned int i = 0; i < keys.size(); i++)
	{
		strMap[keys[i]] = "";
		tablePairs.push_back(TablePair(font, barTex, bgTex, sf::Vector2f(0, i*ySpacing), charSize, xSpacing));
		tablePairs[i].setKeyString(keys[i]);

	}
}


void EntryTable::update(const std::string& curstr, MouseData& mdata)
{
	for (unsigned int i = 0; i < strMap.size(); i++)
	{
		tablePairs[i].update(curstr, mdata);
	}
}

void EntryTable::draw(const sf::Vector2f& drawpos, sf::RenderWindow& window)
{
	position += drawpos;

	for (unsigned int i = 0; i < strMap.size(); i++)
	{
		tablePairs[i].draw(position, window);
	}

	position -= drawpos;
}