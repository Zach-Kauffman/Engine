#pragma once
#include "SFMLbase.h"


class MouseData										//A class for storing data for mouse position, left and right buttons
{
public:

	MouseData();									//constructor


	
	void setMousePosition(sf::Vector2i fposition);	//set mouse position



	void setButtonData(sf::Vector2i fdata);			//set button data (clicked, released, held, unheld)

	void setLeftButtonData(int fdata);				//set the clicked state for the left mouse button

	void setRightButtonData(int fdata);				//set the clicked state for the right mouse button
	


	sf::Vector2i getMousePosition();				//returns the mouse position



	sf::Vector2i getButtonData();					//returns the button data, left and right

	int getLeftButtonData();						//returns only left button data

	int getRightButtonData();						//returns only right button data
	

private:

	sf::Vector2i mousePosition;						//poisition of the mouse

	sf::Vector2i buttonData;						//data for the buttons; .x is the left mouse data, .y is the right mosue data
	
};

