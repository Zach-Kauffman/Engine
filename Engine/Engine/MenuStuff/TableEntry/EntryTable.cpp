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
	const sf::Vector2f& bgSiz, sf::Texture * const fbarTex, const double& findent, const unsigned int& dispAmt)
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
	displayAmt = dispAmt;
	displayInterval = std::make_pair(0, dispAmt - 1);

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
		if (!tablePairs[i].getIsHidden())
		{
			tablePairs[i].update(inpData);
		}


	}




}


void EntryTable::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;

	setTablePositions();
	for (unsigned int i = 0; i < tablePairs.size(); i++)
	{
		if (!tablePairs[i].getIsHidden())
		{
			tablePairs[i].draw(window, position);
		}
	}

	position -= drawPos;
}


//private

void EntryTable::setActivities(InputData& inpData)
{
	if (tablePairs.size())
	{

	
		int currentActiveRow = displayInterval.first;

		bool activityFound = false;

		std::vector<unsigned int> tableIndeces = getDisplayIndeces();
		for (unsigned int i = 0; i < tableIndeces.size(); i++)
		{
			if (tablePairs[tableIndeces[i]].getActivity())
			{
				activityFound = true;
				currentActiveRow = i;
			}
			else if (activityFound)
			{
				tablePairs[tableIndeces[i]].setActivity(false);
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


			if (currentActiveRow > displayInterval.second)
			{
				shiftInterval(currentActiveRow - displayInterval.second);
				currentActiveRow = displayInterval.second;
			}
			if (currentActiveRow < displayInterval.first)
			{
				shiftInterval(currentActiveRow - displayInterval.second);
				currentActiveRow = displayInterval.first;
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


std::vector<unsigned int> EntryTable::getDisplayIndeces()
{
	unsigned int siz = tablePairs.size();
	std::vector<unsigned int> retVec;
	if (displayInterval.first < displayInterval.second)
	{
		for (unsigned int i = displayInterval.first; i <= displayInterval.second; i++)
		{
			retVec.push_back(i);
		}
	}

	else
	{
		for (unsigned int i = displayInterval.first; i != displayInterval.second; i++)
		{
			if (i == siz)
			{
				i = 0;
			}

			retVec.push_back(i);
		}
		retVec.push_back(displayInterval.second);
	}

	return retVec;

}

void EntryTable::shiftInterval(const int& shift)
{
	unsigned int siz = tablePairs.size();

	int fir = (int)displayInterval.first;
	int sec = (int)displayInterval.first;

	fir += shift;
	sec += shift;

	if (fir < 0)
	{
		fir = siz - ((-fir) % siz);
	}
	else
	{
		fir = fir % siz;
	}

	if (sec < 0)
	{
		sec = siz - ((-sec) % siz);
	}
	else
	{
		sec = sec % siz;
	}

	displayInterval.first = fir;
	displayInterval.second = sec;

}

void EntryTable::setTablePositions()
{
	std::vector<sf::Vector2f> positionVec;
	for (unsigned int i = 0; i < displayAmt; i++)
	{
		positionVec.push_back(sf::Vector2f(0, i*(ySpacing + bgSize.y / 2)));
	}

	std::vector<unsigned int> dispIndeces = getDisplayIndeces();
	for (unsigned int i = 0; i < dispIndeces.size(); i++)
	{
		tablePairs[dispIndeces[i]].setPosition(positionVec[i]);
	}




		
}

void EntryTable::setTableHiddenness()
{
	std::vector<unsigned int> dispIndeces = getDisplayIndeces();
	{
			for (unsigned int i = 0; i < tablePairs.size(); i++)
			{
				if(std::find(dispIndeces.begin(), dispIndeces.end(), i) != dispIndeces.end()) 
				{
					tablePairs[i].unhide();
				} 
				else
				{
					tablePairs[i].hide();
				}
			}
	}
}