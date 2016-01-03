#include "Layer.hpp"

//---------------------------
//Not much to see here
//---------------------------


//public

Layer::Layer()
{
}


Layer::~Layer()
{
}


void Layer::setScrollSpeed(const sf::Vector2f& fspeed)
{
	scrollSpeed = fspeed;				//set scroll speed
}

sf::Vector2f Layer::getScrollSpeed()
{
	return scrollSpeed;
}