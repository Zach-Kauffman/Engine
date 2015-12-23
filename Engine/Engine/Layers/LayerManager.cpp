#include "LayerManager.hpp"


LayerManager::LayerManager()
{
	oldReferencePointValue = sf::Vector2f(0, 0);
	layerManagerLogger = logger::getSLogger();
}


LayerManager::~LayerManager()
{
}

void LayerManager::addLayer()
{
	Layer emptyLayer;
	layers.push_back(emptyLayer);
}

Layer& LayerManager::getReferenceToLayer(const int& index)
{
	return layers[index];
}

void setReferencePoint(int*& refPoint)
{
	referencePoint = refPoint;
}


void LayerManager::draw(sf::RenderWindow& window)
{

	sf::Vector2f distance = oldReferencePointValue - *referencePoint;
		
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		sf::Sprite tmpSprite(layers[i].getTexture());
		tmpSprite.move(layers[i].getScrollSpeed.x * distance.x, layers[i].getScrollSpeed.y * distance.y);
		window.draw(tmpSprite);
	}

	oldReferencePointValue = *referencePoint;
}

