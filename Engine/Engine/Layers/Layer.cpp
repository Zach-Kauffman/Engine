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



void setScrollBound(const double& nsBound, const unsigned int& index)
{
	scrollBounds[index] = nsBound;
}

void setAllScrollBounds(const double(&nsBound)[4])	//might not be correct syntax
{
	for (unsigned int i = 0; i < 4; i++)
	{
		scrollBounds[i] = nsBound[i];
	}
}

double getScrollBound(const unsigned int& index)
{
	return scrollBounds[index];
}



void setScrollBoundedness(const bool& nscrollBounded)
{
	scrollBounded = nscrollBounded;
}

bool getScrollBoundedness()
{
	return scrollBounded;
}