#include "HitBox.hpp"


HitBox::HitBox()
{
	typeSet = false;
}


HitBox::~HitBox()
{
}

void HitBox::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void HitBox::setPosition(const double& x, const double& y)
{
	position.x = x;
	position.y = y;
}


void HitBox::move(const sf::Vector2f& disp)
{
	position += disp;
}

void HitBox::move(const double& dx, const double& dy)
{
	position.x += dx;
	position.x += dy;
}

sf::Vector2f HitBox::getPosition()
{
	return position;
}

void HitBox::setType(const unsigned int & type)
{
	if (!typeSet)
	{
		typeSet = true;
		typeID = type;
	}
}


unsigned int HitBox::getType()
{
	return typeID;
}