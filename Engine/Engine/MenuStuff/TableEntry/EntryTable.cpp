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
		tablePairs.push_back(TablePair(font, charSize, color, bgTexture, bgSize, barTexture, sf::Vector2f(0, i*(ySpacing + bgSize.y/2)), indent, xSpacing));
		tablePairs[i].setKeyString(it->first);
		tablePairs[i].setEntryString(it->second);
		i++;
	}

}




void EntryTable::update(InputData& inpData)
{

	setActivities(inpData);
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


//private

void EntryTable::setActivities(InputData& inpData)
{
	if (tablePairs.size())
	{

	
		int currentActiveRow = 0;

		bool activityFound = false;
		for (unsigned int i = 0; i < tablePairs.size(); i++)
		{
			if (tablePairs[i].getActivity())
			{
				activityFound = true;
				currentActiveRow = i;
			}
			else if (activityFound)
			{
				tablePairs[i].setActivity(false);
			}
		}

		if (activityFound)
		{
			bool shift =	inpData.isKeyHeld(sf::Keyboard::LShift) || inpData.isKeyHit(sf::Keyboard::LShift) || 
						inpData.isKeyHeld(sf::Keyboard::RShift) || inpData.isKeyHit(sf::Keyboard::RShift);

			if (inpData.isKeyHit(sf::Keyboard::Down) || (inpData.isKeyHit(sf::Keyboard::Tab) && !shift) || inpData.isKeyHit(sf::Keyboard::Return))
			{
				currentActiveRow++;
			}

			if (inpData.isKeyHit(sf::Keyboard::Up) || (inpData.isKeyHit(sf::Keyboard::Tab) && shift))
			{
				currentActiveRow--;
			}


			if (currentActiveRow >= (int)tablePairs.size())
			{
				currentActiveRow = tablePairs.size() - 1;
			}
			if (currentActiveRow < 0)
			{
				currentActiveRow = 0;
			}

			for (unsigned int i = 0; i < tablePairs.size(); i++)
			{
				if (i == currentActiveRow)
				{
					tablePairs[i].setActivity(true);
				}
				else
				{
					tablePairs[i].setActivity(false);
				}
			}
		}
		
	}
}