#include "Layer.hpp"

//---------------------------
//Not much to see here
//---------------------------


//public

Layer::Layer()
{
	scrollBounded = false;				//by default, scrollBoundedness is false
	scrollTracker = sf::Vector2f(0, 0);	//the scrollTracker starts at (0,0)
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
	scrollBounds[index] = nsBound;		//set individual scroll bound
}

void Layer::setScrollBounds(std::vector<const double> nsBound)
{
										//sets all scroll bounds
	if (nsBound.size() != 4)
	{
		nsBound.resize(4);				//resize to be 4
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		scrollBounds[i] = nsBound[i];	//then copy the vector values into the scrollBounds
	}

}

double Layer::getScrollBound(const unsigned int& index)
{
	return scrollBounds[index];			//returns a specific scroll bound
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

void Layer::setInitTracking(const sf::Vector2f& inTracking)
{
	scrollTracker = inTracking;
}

sf::Vector2f Layer::getScrollDistance(const sf::Vector2f& scrollDist)
{
	//keep track of the scrolling 

	const sf::Vector2f oldTrackVal = scrollTracker;

	scrollTracker.x += scrollSpeed.x * scrollDist.x;
	scrollTracker.y += scrollSpeed.y * scrollDist.y;

	
	//then return the difference between the bounded scrolltracking value and the old scrolltracking value
	if (scrollBounded)
	{
		return (boundScrollTracker() - oldTrackVal);
	}
	else
	{
	
		return (scrollTracker - oldTrackVal);
	}

	
}

//private

sf::Vector2f Layer::boundScrollTracker()
{
	//bound the scrollTracker but doesnt overwrite the value
	double xval = scrollTracker.x;
	double yval = scrollTracker.y;
	util::dbound(xval, scrollBounds[Left], scrollBounds[Right]);
	util::dbound(yval, scrollBounds[Top], scrollBounds[Bottom]);

	//return a new vector equal to the boundsd scrollBound
	return sf::Vector2f(xval, yval);
}