#pragma once
#include "MenuElement.hpp"
#include "SingleTextBox.hpp"
#include "MultiMenuSprite.hpp"
#include "boost\function.hpp"

class Slider : public MenuElement
{
public:

	Slider(sf::Vector2f& position, const sf::Texture& bg, const sf::Texture& indicator, double M, double m, double start, const std::string& text, const unsigned int& charSize);

	//bool getEventDataBool();//so that the class is not abstract
	int getEventDataInt();//returns slider value

	void setButtonTextString(std::string);
	std::string getButtonTextString();

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);
	void update(sf::Vector2f&, bool&, bool&);
	void update(InputData& inpData);//so that the class is not abstract
	void update();

	void resetMD();

private:
	double currentValue, maxValue, minValue;
	float cordScale;
	unsigned int charSize;
	
	sf::Font font;
	SingleTextBox textBox;
	std::string textString;
	AppSprite bgSprite;
	AppSprite slSprite;
	sf::Text text;
	sf::Texture background;
	sf::Texture sliderThing;
	sf::Vector2f textureTLPos;
	sf::Vector2f bgTLPos, bgBRPos;



};
