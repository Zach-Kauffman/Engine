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

void EntryTable::setMap(std::map<std::string, std::string>& fmap)
{
	strMap = &fmap;
	typedef std::map<std::string, std::string>::iterator it_type;
	for(it_type iterator = fmap.begin(); iterator != fmap.end(); iterator++) {
	 // iterator->first = key
		recordstrs.push_back(iterator->first);
	}
}

void EntryTable::createTable(sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex)
{
	for (unsigned int i = 0; i < recordstrs.size(); i++)
	{
		TablePair temp(font, barTex, bgTex, sf::Vector2f(0, i*ySpacing), charSize, xSpacing);
		tablePairs.push_back(temp);
		tablePairs[i].setKeyString(recordstrs[i]);
		tablePairs[i].setEntryString((*strMap)[recordstrs[i]]);
	}


}


void EntryTable::update(const char& typedChar, MouseData& mdata)
{
	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		tablePairs[i].update(typedChar, mdata);
	}
	for (int i = 0; i < recordstrs.size(); i++)
	{
		//std::cout << (*strMap)[recordstrs[i]] << std::endl;
	}
}

void EntryTable::draw(const sf::Vector2f& drawpos, sf::RenderWindow& window)
{
	position += drawpos;

	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		tablePairs[i].draw(position, window);
	}

	position -= drawpos;
}