#include "Animation.cpp"

Animation::Animation()
{
	timer.start();
}

Animation::Animation(const sf::Texture* sprites, const int& fps)
{
	FPS = fps;
	spriteSheet = sprites;
	Animation();
}

Animation::~Animation();

void setFPS(const int& newFPS)
{
	FPS = newFPS;
}

int getFPS()
{
	return FPS:
}

void setSpriteSheet(const sf::Texture* newSpriteSheet)
{
	spriteSheet = newSpriteSheet;
}

sf::Texture* getSpriteSheet()
{
	return spriteSheet;
}

void Animation::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

sf::Vector2f getPosition()
{
	return position;
}

void drawNextFrame(sf::RenderTexture& texture)
{
	prepareNextFrame();		//sets texture coords etc.
	
}


