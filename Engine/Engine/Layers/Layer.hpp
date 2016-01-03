#pragma once
#include <SFML/Graphics.hpp>

class Layer : public sf::RenderTexture					//Layer is a RenderTexture that can have parallax added to it; it is a "small" class
														//because it is a light wrapper of RenderTexture
{

public:

	Layer();											//constructor and destructor are empty
	~Layer();

	void setScrollSpeed(const sf::Vector2f& fspeed);	//set the scrolling speed of the layer; should be pairs of numbers bewtween 0 and 1 inclusive

	sf::Vector2f getScrollSpeed();						//get scroll speed

private:

	sf::Vector2f scrollSpeed;							//the fraction of the "normal" scroll speed at which a layer will scroll; a layer with
														//.5 scroll speed will scroll half as quickly as a layer with 1 scroll speed; a layer with 0
														//scroll speed will be stationary.
};

