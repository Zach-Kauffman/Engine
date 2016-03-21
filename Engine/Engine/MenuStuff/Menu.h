#pragma once

#include "MenuToolsInclude.h"


class Menu																	//a Grouping of menuElements; one example could be a pause menu of options menu
{

public:

	Menu();																	//constructor

	void addMenuElement(MenuElement& fmenuElement, std::string fname);		//adds a menuElement and its name

	void addMenuElement(MenuElement* fmenuElement, std::string fname);		//same thing, just no reference, replaced with pointer



	void setRelativePosition(sf::Vector2f fpos);							//sets the relative position of the menu

	void addRelativePosition(sf::Vector2f velocity);						//adds relative position





	void deactivate();														//deactivates the menu

	void activate();														//activates the menu

	void switchActive();													//switch the activfe states

	void setIsActive(bool factive);											//set the activity to a certain state


	bool getIsActive();														//returns if the menu is active -- don't draw if it is


	MenuElement* getPointerToElementByIndex(int findex);					//gets a pointer to a menuElement by index, NOT A CHILD CLASS

	MenuElement* getPointerToElementByName(std::string fname);				//gets a pointer to a menuElement by name, NOT A CHILD CLASS


	//template<class C> C* getPointerToChildByName(std::string fname);		//gets a pointer to a child by name


	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);										//updates all of the menuElements

	void draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition);	//draws all of the menuElements



private:


	void addElementName(std::string fname);									//adds a menuElement's name to the name map


	std::vector<MenuElement*> elementVector;								//a vector of pointers to menuElements

	std::map<std::string, int> elementNames;								//a mapping of names to indices of menuElements 
	

	sf::Vector2f position;													//the position of the menu (relative)
	
	bool isActive;															//determines if the menu is active
};

