#include "MenuElement.h"


void MenuElement::setPosition(sf::Vector2f fpos)
{
	position = fpos;
}


void MenuElement::move(sf::Vector2f velocity)
{
	position += velocity;
}



sf::Vector2f MenuElement::getPosition()
{
	return position;
}



bool MenuElement::getRequiresMouseData()
{
	return requiresMouseData;
}


void MenuElement::setRequiresMouseData(bool frequiresMouseData)
{
	requiresMouseData = frequiresMouseData;
}




void MenuElement::hide()
{
	isHidden = true;
}



void MenuElement::unhide()
{
	isHidden = false;
}




bool MenuElement::getIsHidden()
{
	return isHidden;
}



void MenuElement::setResetsOnMD(bool fresetsOnMD)
{

	resetsOnMD = fresetsOnMD;

}

bool MenuElement::getResetsOnMD()
{
	return resetsOnMD;
}