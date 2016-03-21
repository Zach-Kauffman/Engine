#pragma once
#include "MenuElement.h"
#include "AppSprite.h"


class MenuSprite : public MenuElement												//This class is a sprite that is also a menuElement, essentially
{

public:

	MenuSprite();																	//0-argument constructor

	MenuSprite(const sf::Texture* const ftexture, sf::Vector2f fposition, sf::Vector2f fsize);	//constructor with all elements

	~MenuSprite();																	//destructor


	void setup(const sf::Texture* const ftexture, sf::Vector2f fposition, sf::Vector2f fsize);	//sets up the MenuSprite


	//inherited virtuals
	void update();

	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);

	void draw(sf::RenderWindow& frenderWindow, sf::Vector2f drawPosition);

	void resetMD();															




	sf::Vector2f getGlobalDimensions();												//returns the dimensions of the MenuSprite globally

	sf::Vector2f getLocalDimensions();												//returns the dimensions of the MenuSprite locally

private:

	AppSprite menuImage;															//the AppSprite that Menusprite is just a wrappedd version of.

};

