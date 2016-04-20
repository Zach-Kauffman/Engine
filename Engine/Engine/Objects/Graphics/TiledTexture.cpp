#include "TiledTexture.hpp"

TiledTexture::TiledTexture(){}

TiledTexture::TiledTexture(sf::Texture* newTexture, sf::Vector2f* newPosition, sf::Vector2f* newSize, const sf::Vector2f& newSetSize)
{
	centerPosition = newPosition;
	drawPosition = *centerPosition;
	setSize = newSetSize;
	tile = Texture(newTexture, &drawPosition, newSize);
}

void TiledTexture::draw(sf::RenderTexture& render)
{
	for (int xit = 0; xit < setSize.x; xit++)
	{
		for (int yit = 0; yit < setSize.y; yit++)
		{
			drawPosition = sf::Vector2f(centerPosition->x + tile.getSize()->x, centerPosition->y + tile.getSize()->y);
		}
	}
}

void TiledTexture::update()
{

}