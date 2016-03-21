#include "Menu.h"


Menu::Menu()															//Constructor
{
	isActive = true;													//isActive is true at the start
	position = sf::Vector2f(0, 0);										//position is 0,0 at the start
}


void Menu::addMenuElement(MenuElement& fmenuElement, std::string fname)	//adds a menuElement
{
	elementVector.push_back(&fmenuElement);								//adds a pointer to a menuElement

	addElementName(fname);												//adds the name
}



void Menu::addMenuElement(MenuElement* fmenuElement, std::string fname)
{
	elementVector.push_back(fmenuElement);								//adds a pointer to a menuElement

	addElementName(fname);												//adds the name
}



void Menu::setRelativePosition(sf::Vector2f fpos)						//set the relative position of the menu
{
	//sf::Vector2f oldPos = position;			

	position = fpos;													//change to the new position

	//sf::Vector2f distance(oldPos - position);							
	
	//for (unsigned int i = 0; i < elementVector.size(); i++)
	//{
	//	elementVector[i]->move(distance);
	//}
}



void Menu::addRelativePosition(sf::Vector2f velocity)					//add position to the menu
{

	position += velocity;												//add velocity to position

}



void Menu::deactivate()													//deactivates the menu
{

	isActive = false;													//isActive is turned to false

	for (unsigned int i = 0; i < elementVector.size(); i++)
	{
		if (elementVector[i]->getResetsOnMD())
		{
			elementVector[i]->resetMD();
		}
	}

}



void Menu::activate()													//activates the menu
{

	isActive = true;													//isActive is turned to true

}


void Menu::switchActive()												//switches the activity of the menu
{

	setIsActive(!isActive);

}


void Menu::setIsActive(bool factive)									//sets the activity of the menu
{

	if (factive)
	{
		activate();
	}
	else
	{
		deactivate();
	}

}


bool Menu::getIsActive()												//returns if the menu is active
{

	return isActive;													//returns isActive

}



MenuElement* Menu::getPointerToElementByIndex(int findex)				//gets a pointer to a menuElement, not a child
{

	return elementVector[findex];										//returns the findex'th part of elementVector

}



MenuElement* Menu::getPointerToElementByName(std::string fname)			//returns a pointer to a menuElemtn by nake, not a child
{

	return elementVector[elementNames[fname]];							//returns the (int that the name was mapped to)th element of elementVector

}


void Menu::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)								//updates all of the menuElements
{
	for (unsigned int i = 0; i < elementVector.size(); i++)				//cycle through all menuElements
	{
		if (elementVector[i]->getRequiresMouseData())					//if it requires mouse data
		{
			elementVector[i]->update(fmouseData, typedChar, fkeyData);						//give it mouse data
		}
		else															//otherwise
		{
			elementVector[i]->update();									//just update it
		}
	}
}



void Menu::draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition)	//draws all of the menuElements
{
	position += drawPosition;												//adds the draw position to make position relative

	for (unsigned int i = 0; i < elementVector.size(); i++)					//cycle through all menuElements
	{
		if (!elementVector[i]->getIsHidden())								//if its not hidden
		{
			elementVector[i]->draw(frenderwindow, position);				//draw it
		}
	}

	position -= drawPosition;												//subtract the draw position because we added it
}






//private

void Menu::addElementName(std::string fname)						//adds a name to the nameMap
{
	bool sameName = true;											//same name starts of as true

	bool firstDuplicate = true;										//first duplicate is true

	while (sameName == true)										//until nothing has the same name
	{

		if (elementNames.count(fname) == 1)							//if there exists a thing with that name already
		{
			if (firstDuplicate == true)								//if it was the first duplicate
			{
				fname += "2";										/*if there exists a "ExitButton" already, and you try to add another one,
																	it will become "ExitButton2"*/

				firstDuplicate = false;								//there cant be more than one first duplicate
			}
			else
			{
				fname[fname.size() - 1]++;							/*if there exists a "ExitButton2" already, and you try to add another one,
																	it will become "ExitButton3"*/
			}
		}

		else
		{
			sameName = false;										//if there is no same name, exit the while loop
		}

	}

	elementNames[fname] = elementVector.size() - 1;					//then add the altered (or not) name
}

