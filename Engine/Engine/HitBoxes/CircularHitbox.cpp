#include "CircularHitbox.hpp"


CircularHitbox::CircularHitbox()
{
}


CircularHitbox::~CircularHitbox()
{
}

void CircularHitbox::setRadius(const double& rad)
{
	radius = rad;
}

bool CircularHitbox::isPointInside(const sf::Vector2f& point)
{
	bool inside = false;
	
	sf::Vector2f ndist = point - position;

	if (fabs(ndist.x * ndist.x + ndist.y * ndist.y - radius * radius) < .001)
	{
		inside = true;
	}

	return inside;
}

