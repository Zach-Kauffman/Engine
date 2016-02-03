#include "Layer.hpp"


//public

Layer::Layer()
{
	scrollBounded = false;				//by default, scrollBoundedness is false
	scrollSpeed = sf::Vector2f(1, 1);
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




void Layer::setExtremeCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner)
{
	setTopLeftCorner(fTLCorner);
	setBottomRightCorner(fBRCorner);
}

void Layer::setExtremeCornersAlt(const sf::Vector2f& fBLCorner, const sf::Vector2f& fTRCorner)
{
	setTopRightCorner(fTRCorner);
	setBottomLeftCorner(fBLCorner);
}

void Layer::setTopLeftCorner(const sf::Vector2f& fTLCorner)
{
	TLCorner = fTLCorner;
	initTLCorner = fTLCorner;
}

void Layer::setBottomRightCorner(const sf::Vector2f& fBRCorner)
{
	BRCorner = fBRCorner;
	initBRCorner = fBRCorner;
}

void Layer::setBottomLeftCorner(const sf::Vector2f& fBLCorner)
{
	TLCorner.x = fBLCorner.x;
	initTLCorner.x = fBLCorner.x;

	BRCorner.y = fBLCorner.y;
	initBRCorner.y = fBLCorner.y;
}

void Layer::setTopRightCorner(const sf::Vector2f& fTRCorner)
{
	TLCorner.y = fTRCorner.y;
	initTLCorner.y = fTRCorner.y;

	BRCorner.x = fTRCorner.x;
	initBRCorner.x = fTRCorner.x;
}




float Layer::getMinWindowX()
{
	return TLCorner.x;
}

float Layer::getMaxWindowX()
{
	return BRCorner.x;
}

float Layer::getMinWindowY()
{
	return TLCorner.y;
}

float Layer::getMaxWindowY()
{
	return BRCorner.y;
}

std::pair<sf::Vector2f, sf::Vector2f> Layer::getWindowCorners()
{
	return std::make_pair(TLCorner, BRCorner);
}



//
//void Layer::setInitTracking(const sf::Vector2f& inTracking)
//{
//	scrollTracker = inTracking;
//}

sf::Vector2f Layer::getScrollDistance(const sf::Vector2f& scrollDist)
{
	//keep track of the scrolling 


	sf::Vector2f dist;
	dist.x = scrollSpeed.x * scrollDist.x;
	dist.y = scrollSpeed.y * scrollDist.y;

	//scrollTracker = dist;

moveCorners(dist);

	
	//then return the difference between the bounded scrolltracking value and the old scrolltracking value
	
	if (scrollBounded)
	{
		const sf::Vector2f corDist = getCorrectiveDistance();						//get the corrective distance that will align the layer to the bounds 

		moveCorners(corDist);

		const sf::Vector2f retTmp = (dist + corDist);	//should be 0 if the scrollTracker was out of bounds last time

		//oldScrollTracker = scrollTracker + corDist;

		return retTmp;

	}
	else
	{
		return dist;
		
	}
	
}



sf::RenderTexture* Layer::getRenderTexture()
{
	return &renderTex;
}



//private

void Layer::moveCorners(const sf::Vector2f& dist)
{
	TLCorner = initTLCorner + dist;
	BRCorner = initBRCorner + dist;
}

sf::Vector2f Layer::getCorrectiveDistance()
{
	//gets the distance required to align the corners with the scrollBunds

	//finds the difference in bounds derived from the corners and the desired bounds. If there is no undesired occurrence, it will be 0
	double xval = 0;
	if (TLCorner.x < scrollBounds[Left])
	{
		xval = scrollBounds[Left] - TLCorner.x;
	}
	else if (BRCorner.x > scrollBounds[Right])
	{
		xval = scrollBounds[Right] - BRCorner.x;
	}

	double yval = 0;
	if (TLCorner.y < scrollBounds[Top])
	{
		yval = scrollBounds[Top] - TLCorner.y;
	}
	else if (BRCorner.y > scrollBounds[Bottom])
	{
		yval = scrollBounds[Bottom] - BRCorner.y;
	}


	//return the required distance
	return sf::Vector2f(xval, yval);
}
