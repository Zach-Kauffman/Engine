#include "HitBox.hpp"


HitBox::HitBox()
{
}


HitBox::~HitBox()
{
}

void HitBox::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void HitBox::move(const sf::Vector2f& disp)
{
	position += disp;
}