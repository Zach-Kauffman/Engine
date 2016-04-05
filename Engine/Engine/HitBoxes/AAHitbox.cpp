#include "AAHitbox.hpp"


AAHitbox::AAHitbox()
{
}


AAHitbox::~AAHitbox()
{
}

void AAHitbox::setSize(const sf::Vector2f& siz)
{
	setCorners(sf::Vector2f(position.x - siz.x / 2, position.y - siz.y / 2), sf::Vector2f(position.x + siz.x / 2, position.y + siz.y / 2));
}

void AAHitbox::setCorners(const sf::Vector2f& tl, const sf::Vector2f& br)
{
	TLCorner = tl;
	BRCorner = br;
}

bool AAHitbox::isPointInside(const sf::Vector2f& point)
{
	bool inside = false;

	double bounds[4];
	bounds[Top] = TLCorner.y;
	bounds[Bot] = BRCorner.y;
	bounds[Left] = TLCorner.x;
	bounds[Right] = BRCorner.x;

	if (bounds[Top] <= point.y && bounds[Right] >= point.x && bounds[Bot] >= point.y && bounds[Left] <= point.x)
	{
		inside = true;
	}
	return inside;
}