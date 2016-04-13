#include "Animation.hpp"

Animation::Animation()
{
	frameTimer.restart();
	lastFrameTime = -1;
	texCoords = sf::VertexArray(sf::Quads, 4);
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize)
{
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	calcFps();
	Animation();
	prepareAnimation();
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const int& newFps)
{
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	setFPS(newFps);
	Animation();
	prepareAnimation();
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const int& newFps, const sf::Vector2f& position)
{
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	setFPS(newFps);
	setPosition(position);
	Animation();
	prepareAnimation();
}

Animation::~Animation(){}

void Animation::setFPS(const int& newFPS)
{
	fps = newFPS;
	desiredFrameTime = 1.0 / fps;
}

int Animation::getFPS()
{
	return fps;
}

void Animation::setFrameSize(const sf::Vector2f& newFrameSize)
{
	frameSize = newFrameSize;
}

sf::Vector2f Animation::getFrameSize()
{
	return frameSize;
}

void Animation::setSpriteSheet(sf::Texture* newSpriteSheet)
{
	spriteSheet = newSpriteSheet;
	if (!fps)
	{
		calcFps();
	}
}

sf::Texture* Animation::getSpriteSheet()
{
	return spriteSheet;
}

void Animation::setPosition(const sf::Vector2f& newPosition)
{
	position = &newPosition;
	lastPosition = newPosition;
}

void Animation::drawNextFrame(sf::RenderTexture& texture)
{
	if (lastFrameTime - frameTimer.elapsed() >= desiredFrameTime)		//if its been more than 1/fps since the last frame
	{
		prepareNextFrame();		//sets texture coords etc.
		lastFrameTime = frameTimer.elapsed();
	}
	updatePosition();
	texture.draw(texCoords, spriteSheet);
}

//PROTECTED FUNCTIONS
void Animation::prepareNextFrame()
{
	for (int i = 0; i < texCoords.getVertexCount(); i++)
	{
		if (currentSheetPosition.x < sheetSize.x)
		{
			texCoords[i].texCoords.x += frameSize.x;
			currentSheetPosition.x++;
		}
		else if(currentSheetPosition.y < sheetSize.y)
		{
			texCoords[i].texCoords.y += frameSize.y;
		}
		else
		{
			currentSheetPosition = sf::Vector2f(1, 1);	//reset to first texture
			texCoords[i].texCoords -= sf::Vector2f(frameSize.x * sheetSize.x-1, frameSize.y * sheetSize.y-1);
		}

	}
}

void Animation::updatePosition()
{
	for (int i = 0; i < texCoords.getVertexCount(); i++)
	{
		texCoords[i].position += (*position - lastPosition);
	}
	lastPosition = *position;
}

void Animation::prepareAnimation()
{
	sheetSize.x = spriteSheet->getSize().x / frameSize.x;
	sheetSize.y = spriteSheet->getSize().y / frameSize.y;

	texCoords = sf::VertexArray(sf::Quads, 4);
	texCoords[0].position = sf::Vector2f((*position).x + frameSize.x / 2, (*position).y + frameSize.y / 2);	//bottom right
	texCoords[1].position = sf::Vector2f((*position).x - frameSize.x / 2, (*position).y + frameSize.y / 2);		//bottom left
	texCoords[2].position = sf::Vector2f((*position).x - frameSize.x / 2, (*position).y - frameSize.y / 2);		//top left
	texCoords[3].position = sf::Vector2f((*position).x + frameSize.x / 2, (*position).y - frameSize.y / 2);		//top right

	texCoords[0].texCoords = sf::Vector2f(frameSize.x, frameSize.y);		//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, frameSize.y);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(0, 0);							//top left
	texCoords[3].texCoords = sf::Vector2f(frameSize.x, 0);					//top right
}
void Animation::calcFps()	//if no fps is specified, fps is assumed to be 
{
	
}