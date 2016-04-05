#pragma once
#include <SFML\Graphics.hpp>
class HitBox
{
public:
	HitBox();
	~HitBox();

	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& disp);

	virtual bool isPointInside(const sf::Vector2f& point) = 0;

protected:

	sf::Vector2f position;

	
};

