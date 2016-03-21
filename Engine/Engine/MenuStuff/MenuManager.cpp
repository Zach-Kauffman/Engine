#include "MenuManager.h"




MenuManager::MenuManager()															//empty constructor
{

}



void MenuManager::addMenu(Menu fmenu, std::string fname)							//adds a menu
{

	menuVector.push_back(fmenu);													//add the menu

	addMenuName(fname);																//add the name of the menu

	drawPositions.push_back(sf::Vector2f(0, 0));									//automatically makes a new drawPosition

}



void MenuManager::addMenu(Menu fmenu, std::string fname, sf::Vector2f fdrawPosition)
{
	menuVector.push_back(fmenu);													//add the menu

	addMenuName(fname);																//add the name of the menu

	drawPositions.push_back(fdrawPosition);											//add the given drawPosition		
}



Menu* MenuManager::getMenuPointerByName(std::string fname)							//returns a pointer to a menu
{

	Menu* tmpMenuPointer = &menuVector[menuNames[fname]];							//makes a temporary pointer that points to a menu

	return tmpMenuPointer;															//return it

}




void MenuManager::setMenuDrawPositionByName(std::string fname, sf::Vector2f fpos)	//sets a drawPoisiton of one of the menus by name
{

	drawPositions[menuNames[fname]] = fpos;											//set the drawPosition by name

}




void MenuManager::moveMenuDrawPositionByName(std::string fname, sf::Vector2f fvel)	//add position to a drawPoisiton of a menu by name
{
	drawPositions[menuNames[fname]] += fvel;										//increment the drawPosition by the desired velocity
}



void MenuManager::activateAllMenus()
{
	for (unsigned int i = 0; i < menuVector.size(); i++)
	{
		menuVector[i].activate();
	}
}



void MenuManager::deactivateAllMenus()
{
	for (unsigned int i = 0; i < menuVector.size(); i++)
	{
		menuVector[i].deactivate();
	}
}



void MenuManager::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)										//updates the menus
{
	for (unsigned int i = 0; i < menuVector.size(); i++)							//cycle through all the menus
	{
		if (menuVector[i].getIsActive())
		{
			menuVector[i].update(fmouseData, typedChar, fkeyData);											//update them
		}
	}
}



void MenuManager::draw(sf::RenderWindow& frenderwindow)								//draws all the menus
{
	for (unsigned int i = 0; i < menuVector.size(); i++)							//cycle through all of the menus
	{
		if (menuVector[i].getIsActive())
		{
			menuVector[i].draw(frenderwindow, drawPositions[i]);						//draw them all at their respective drawPositions
		}
	}
}



//private


void MenuManager::addMenuName(std::string fname)									//adds a name to the name map
{
	bool sameName = true;
	bool firstDuplicate = true;

	while (sameName == true)
	{

		if (menuNames.count(fname) == 1)
		{
			if (firstDuplicate == true)
			{
				fname += "2";										/*if there exists a "OptionsMenu" already, and you try to add another one,
																	it will become "OptionsMenu2"*/
				firstDuplicate = false;
			}
			else
			{
				fname[fname.size() - 1]++;							/*if there exists a "OptionsMenu2" already, and you try to add another one,
																	it will become "OptionsMenu3"*/
			}
		}

		else
		{
			sameName = false;										//if there is no same name, exit the while loop
		}

	}

	menuNames[fname] = menuVector.size() - 1;					//then add the altered (or not) name
}

