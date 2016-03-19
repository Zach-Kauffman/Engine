#pragma once

#include "IncludeMe.h"

class MenuElement
{
public:


	virtual void update() = 0;															//virtual; every menuElement will have a 0-argument update

	virtual void update(MouseData& fmouseData) = 0;										//and they will have a 1-argument mousedata update

	virtual void draw(sf::RenderWindow& frenderWindow, sf::Vector2f drawPosition) = 0;	//and will draw, somehow

	virtual void resetMD() = 0;															//reset on menu deactivation





	

	void setPosition(sf::Vector2f fpos);												//set the position of a menuElement

	void move(sf::Vector2f velocity);													//move the menuElement

	sf::Vector2f getPosition();															//retrieve the position of a menuElement
		



	void setRequiresMouseData(bool frequiresMouseData);									//set if something requires mouseData

	bool getRequiresMouseData();														//retrieve mousedata



	void hide();																		//hide a menuElement from drawing

	void unhide();																		//unhide one

	bool getIsHidden();																	//retrieve oif the thing wnats to be drawn

	
	void setResetsOnMD(bool fresetOnMD);

	bool getResetsOnMD();




protected:

	sf::Vector2f position;																//position of the menuElement


	bool requiresMouseData;																//if it requires mouseData

	bool isHidden;																		//if it wants to be drawn

	bool resetsOnMD;																	//if it resets on Menu deactivation
};

