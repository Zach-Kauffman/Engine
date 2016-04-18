#include "HitBox.hpp"


HitBox::HitBox()
{
	position = &sf::Vector2f(0, 0);	//default position to prevent errors
}

HitBox::~HitBox(){}

void HitBox::updatePosition()
{
	hitbox.clear();

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		hitbox.push_back(*position + polygon[i]);
	}
}

std::vector<sf::Vector2f> HitBox::get()
{
	return hitbox;
}
void HitBox::setPosition(sf::Vector2f& pos)
{
	position = &pos;
	updatePosition();
}

void HitBox::create(const std::vector<sf::Vector2f>& points)
{
	polygon = points;
	
}

void HitBox::create(const float& radius, const int& resolution)
{
	polygon.clear();

	double increment = (2 * 3.1415) / resolution;
	for (unsigned int i = 0; i < resolution; i++)
	{
		polygon.push_back(sf::Vector2f(radius * cos(increment * i), radius * sin(increment * i)));
	}
	updatePosition();
}

void HitBox::create(const sf::Vector2f& dimensions)
{
	polygon.clear();
	polygon.push_back(sf::Vector2f(dimensions.x * -1 / 2, dimensions.y*-1 / 2));
	polygon.push_back(sf::Vector2f(dimensions.x / 2, dimensions.y*-1 / 2));
	polygon.push_back(sf::Vector2f(dimensions.x / 2, dimensions.y / 2));
	polygon.push_back(sf::Vector2f(dimensions.x *-1 / 2, dimensions.y / 2));

	updatePosition();
}

sf::Vector2f HitBox::getPosition()
{
	return *position;
}

void HitBox::move(sf::Vector2f& newPosition)
{
	position = &newPosition;
	hitbox.clear();

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		hitbox.push_back(*position + polygon[i]);
	}
}
