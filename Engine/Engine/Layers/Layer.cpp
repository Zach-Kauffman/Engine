#include "Layer.hpp"

//---------------------------
//Not much to see here
//---------------------------


//public

Layer::Layer()
{
	scrollBounded = false;				//by default, scrollBoundedness is false
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



void Layer::setScrollBounds(const double& nsBound, const unsigned int& index)
{
	scrollBounds[index] = nsBound;
}

void Layer::setScrollBounds(std::vector<const double> nsBound)
{
	if (nsBound.size() != 4)
	{
		nsBound.resize(4);
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		scrollBounds[i] = nsBound[i];
	}

}

double Layer::getScrollBound(const unsigned int& index)
{
	return scrollBounds[index];
}

void Layer::setScrollBoundedness(const bool& nscrollBounded)
{
	scrollBounded = nscrollBounded;
}

bool Layer::getScrollBoundedness()
{
	return scrollBounded;
}


void Layer::setWindowDimesions(const sf::Vector2f& newDimens)
{
	windowDimensions = newDimens;
}

sf::Vector2f Layer::getWindowDimensions()
{
	return windowDimensions;
}