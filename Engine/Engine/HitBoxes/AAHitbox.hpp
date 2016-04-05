#pragma once
#include "HitBox.hpp"

class AAHitbox : public HitBox
{
public:
	AAHitbox();
	~AAHitbox();

	void setSize(const sf::Vector2f& siz);
	void setCorners(const sf::Vector2f& tl, const sf::Vector2f& br);
	bool isPointInside(const sf::Vector2f& point);

private:

	sf::Vector2f TLCorner;
	sf::Vector2f BRCorner;

	enum boundvals {Top = 0, Right, Bot, Left};
};

