#pragma once
#include "Layer.hpp"
#include "../Logger.hpp"
#include <vector>


class LayerManager
{
public:
	LayerManager();
	~LayerManager();

	void addLayer();

	Layer& getReferenceToLayer(const int& index);

	void setReferencePoint(int*& refPoint);

	void draw(sf::RenderWindow& window);

	

private:

	sf::Vector2f* referencePoint;
	sf::Vector2f oldReferencePointValue;

	std::vector<Layer> layers;

	src::severity_logger<severity_level> layerManagerLogger;
};

