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


EntryTable::EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos)
{

	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	


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

void EntryTable::createTable(	sf::Font * const ffont, const sf::Color& fcolor, sf::Texture* const bgTex,
								const sf::Vector2f& bgSiz, sf::Texture * const barTex, const double& indent
							)
{
	for (unsigned int i = 0; i < recordstrs.size(); i++)
	{
		
		tablePairs.push_back(TablePair(ffont, charSize, fcolor, bgTex, bgSiz, barTex, sf::Vector2f(0, i*ySpacing), indent, xSpacing));
		tablePairs[i].setKeyString(recordstrs[i]);
		tablePairs[i].setEntryString((*strMap)[recordstrs[i]]);
	}


}


void EntryTable::update(InputData& inpData)
{
	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		tablePairs[i].update(inpData);
	}
	//for (int i = 0; i < recordstrs.size(); i++)
	//{
	//	//std::cout << (*strMap)[recordstrs[i]] << std::endl;
	//}
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