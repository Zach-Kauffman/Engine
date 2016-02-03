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



void Layer::create()
{

	if (!renderTex.create(boundBRCorner.x - boundTLCorner.x, boundBRCorner.y - boundTLCorner.x))
	{

	}

	renderTex.clear(sf::Color(0, 0, 0, 0));
	
	view.setSize(boundBRCorner.x - boundTLCorner.x, boundBRCorner.y - boundTLCorner.x);
	view.setCenter((boundBRCorner.x + boundTLCorner.x) / 2, (boundBRCorner.y + boundTLCorner.y) / 2);

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
	boundTLCorner = fTLCorner;
	trackTLCorner = fTLCorner;
}

void Layer::setBottomRightCorner(const sf::Vector2f& fBRCorner)
{
	boundBRCorner = fBRCorner;
	trackBRCorner = fBRCorner;
}

void Layer::setBottomLeftCorner(const sf::Vector2f& fBLCorner)
{
	boundTLCorner.x = fBLCorner.x;
	trackTLCorner.x = fBLCorner.x;

	boundBRCorner.y = fBLCorner.y;
	trackBRCorner.y = fBLCorner.y;
}

void Layer::setTopRightCorner(const sf::Vector2f& fTRCorner)
{
	boundTLCorner.y = fTRCorner.y;
	trackTLCorner.y = fTRCorner.y;

	boundBRCorner.x = fTRCorner.x;
	trackBRCorner.x = fTRCorner.x;
}




float Layer::getMinWindowX()
{
	return boundTLCorner.x;
}

float Layer::getMaxWindowX()
{
	return boundBRCorner.x;
}

float Layer::getMinWindowY()
{
	return boundTLCorner.y;
}

float Layer::getMaxWindowY()
{
	return boundBRCorner.y;
}

std::pair<sf::Vector2f, sf::Vector2f> Layer::getWindowCorners()
{
	return std::make_pair(boundTLCorner, boundBRCorner);
}



//
//void Layer::setInitTracking(const sf::Vector2f& inTracking)
//{
//	scrollTracker = inTracking;
//}
void Layer::interpretViewPos(const sf::Vector2f& scrollDist)
{


	sf::Vector2f dist;
	dist.x = scrollSpeed.x * scrollDist.x;
	dist.y = scrollSpeed.y * scrollDist.y;


	moveBoundCorners(dist);
	moveTrackCorners(dist);

	
	//then return the difference between the bounded scrolltracking value and the old scrolltracking value
	
	if (scrollBounded)
	{
		const sf::Vector2f corDist = getCorrectiveDistance();						//get the corrective distance that will align the layer to the bounds 

		moveBoundCorners(corDist);

		view.move(dist + corDist);

	}
	else
	{
		view.move(dist);
	}
	
	renderTex.setView(view);
}



sf::RenderTexture* Layer::getRenderTexture()
{
	return &renderTex;
}



//private

void Layer::moveBoundCorners(const sf::Vector2f& dist)
{
	boundTLCorner += dist;
	boundBRCorner += dist;
}

void Layer::moveTrackCorners(const sf::Vector2f& dist)
{
	trackTLCorner += dist;
	trackBRCorner += dist;
}

sf::Vector2f Layer::getCorrectiveDistance()
{
	//gets the distance required to align the corners with the scrollBunds

	//finds the difference in bounds derived from the corners and the desired bounds. If there is no undesired occurrence, it will be 0
	double xval = 0;
	if (trackTLCorner.x < scrollBounds[Left])
	{
		xval = scrollBounds[Left] - boundTLCorner.x;
	}
	else if (trackBRCorner.x > scrollBounds[Right])
	{
		xval = scrollBounds[Right] - boundBRCorner.x;
	}

	double yval = 0;

	if (trackTLCorner.y < scrollBounds[Top])
	{
		yval = scrollBounds[Top] - boundTLCorner.y;
	}
	else if (trackBRCorner.y > scrollBounds[Bottom])
	{
		yval = scrollBounds[Bottom] - boundBRCorner.y;
	}


	//return the required distance
	return sf::Vector2f(xval, yval);
}
