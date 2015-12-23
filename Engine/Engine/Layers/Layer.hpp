#pragma once
#include <SFML/Graphics.hpp>
class Layer : sf::RenderTexture
{

public:

	Layer();
	~Layer();

	void setScrollSpeed(const sf::Vector2f& fspeed);

	sf::Vector2f getScrollSpeed();

private:

	sf::Vector2f scrollSpeed;

};

