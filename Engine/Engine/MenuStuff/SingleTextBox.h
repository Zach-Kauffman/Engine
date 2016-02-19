#pragma once
#include "MenuElement.h"

class SingleTextBox : public MenuElement									//This class is simply text on the screen that has been wrapped a bit																	
{

public:

	SingleTextBox();														//constructor empty

	SingleTextBox(sf::Vector2f fposition, const sf::Font* ffont, std::string fstring, int ffontsize, double fmaxwidth, sf::Color fcolor);
																			//constructor that actually sets everything

	~SingleTextBox();														//destructor
		
	void setup(sf::Vector2f fposition, const sf::Font* ffont, std::string fstring, int ffontsize, double fmaxwidth, sf::Color fcolor);
																			//setup -- must run if empty constructor was used


	//inherited virtual
	void update();

	void update(MouseData& fmouseData);

	void draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition);

	void resetMD();



	void setTextString(std::string fstring);								//set the string of the text

	void setTextColor(sf::Color fcolor);									//set the color of the text

	void setFontSize(int fsize);											//set the font size of the text

private:

	void wrapText();														//wraps the text around the edge of the textbox

	//void resetSize();

	sf::Vector2f getDimensionsOfString(std::string fstr);					//gets the dimension of a hypothetical text under the current conditions

	void correctPosition();													//corrects the position of the text; text is weird: the origin is the center point of the line the first line is written on



	sf::Text textBody;														//the actual text

	sf::Color textColor;													//the text color

	std::string drawString;													//the string to draw

	int characterSize;														//the character size

	double width;															//the width of the textbox

																			//------------much of this stuff is moved one layer out of textBody  for easy access

};

