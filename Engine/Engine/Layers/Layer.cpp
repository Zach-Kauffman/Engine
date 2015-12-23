#include "Layer.hpp"


Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::setScrollSpeed(const sf::Vector2f& fspeed)
{
	scrollSpeed = fspeed;
}

sf::Vector2f Layer::getScrollSpeed()
{
	return scrollSpeed;
}