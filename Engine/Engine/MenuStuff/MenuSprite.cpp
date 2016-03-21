#include "MenuSprite.h"



MenuSprite::MenuSprite()
{
	requiresMouseData = false;			//by default, the MenuSprite does not require mouse data

	isHidden = false;					//it shall be drawn

	resetsOnMD = false;					//it does not reset when the menu deactivates
}


MenuSprite::MenuSprite(const sf::Texture* const ftexture, sf::Vector2f fposition, sf::Vector2f fsize)
{
	requiresMouseData = false;			//same stuff

	isHidden = false;

	resetsOnMD = false;

	setup(ftexture, position, fsize);	//setup	
}



MenuSprite::~MenuSprite()
{

}


void MenuSprite::setup(const sf::Texture* const ftexture, sf::Vector2f fposition, sf::Vector2f fsize)
{
	position = fposition;				//position is set

	menuImage.setup(ftexture, sf::Vector2f(0, 0), fsize, 0);
}



void MenuSprite::update()	//empty
{

}


void MenuSprite::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)	//empty
{

}



void MenuSprite::draw(sf::RenderWindow& frenderWindow, sf::Vector2f drawPosition)
{

	position += drawPosition;		//add the drawPosition  to make position relative
		

		
	menuImage.draw(frenderWindow, position);


	position -= drawPosition;		//subtract the drawPosition because we added it

}


void MenuSprite::resetMD()			//resetMD()
{

}


sf::Vector2f MenuSprite::getGlobalDimensions()													//all this function does is literally return the global
																								//dimensions of the Sprite
{
	return menuImage.getGlobalDimensions();
}



sf::Vector2f MenuSprite::getLocalDimensions()													//same thing as above, except the dimensions are local
{
	return menuImage.getLocalDimensions();
}
