#pragma once
#include "Menu.h"


class MenuManager															//holds menus
{
public:

	MenuManager();															//constructor


	void addMenu(Menu fmenu, std::string fname);							//adds a menu

	void addMenu(Menu fmenu, std::string fname, sf::Vector2f fdrawPosition);//adds a menu and its drawPosition

	Menu* getMenuPointerByName(std::string fname);							//returns a pointer to a menu



	void setMenuDrawPositionByName(std::string fname, sf::Vector2f fpos);	//sets a menu's drawPosition by name

	void moveMenuDrawPositionByName(std::string fname, sf::Vector2f fvel);	//adds a menu's drawPosition by name



	void activateAllMenus();												//activates all menus

	void deactivateAllMenus();												//deactivates all menus



	void update(MouseData& fmousedata);										//updates all of the menus

	void draw(sf::RenderWindow& frenderwindow);								//draws all of the menus


private:

	void addMenuName(std::string fname);									//add a menus name to the name mapping


	std::vector<Menu> menuVector;											//vector of all the menus

	std::vector<sf::Vector2f> drawPositions;								//vector of all the draw positions; they indirectly correspond to menus

	std::map<std::string, int> menuNames;									//maps names to indices for the menus;

};

