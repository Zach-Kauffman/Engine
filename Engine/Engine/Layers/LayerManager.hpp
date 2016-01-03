#pragma once
#include "Layer.hpp"
#include "../Logger.hpp"
#include <vector>


class LayerManager										//holds and manages layers of graphics -- useful for parallax
{
public:

	LayerManager();										//constructor

	LayerManager(const int& amt);						//overloaded to dictate amount of layers at creation

	LayerManager(sf::Vector2f& refPoint);				//overloaded to specify the reference point at creation

	LayerManager(sf::Vector2f& refPoint, const int& amt);
														//overloaded to specify amount of layers and refernce point

	~LayerManager();									//nothing in destructor


	void addEmptyLayer();								//adds a new, empty layer

	void addLayer(Layer newLayer);						//adds an existant layer

	void setLayerAmount(const int& amt);				//sets the amount of layers -- ideally used once only

	void setScrollSpeed(const sf::Vector2f& speed, const int& index);
														//set the scroll speed of a particular layer


	void setAllScrollSpeeds(const std::vector<const sf::Vector2f>& scrollSpeeds);
														//set the scroll speed of all layers; should start with 1 and descend

	Layer* getLayerPointer(const int& index);			//gets a pointer to a layer


	void setReferencePoint(sf::Vector2f& refPoint);		//sets the point that the layers will center on


	void draw(sf::RenderWindow& window);				//draws all of the layers

	

private:

	void basicSetup();									//setup called in every constructor


	int imax(int& a, int& b);							//finds the greater of two ints

	int imin(int& a, int& b);							//finds the lesser of two ints


	sf::Vector2f* referencePoint;						//The point the LayerManager is centered on

	sf::Vector2f oldReferencePointValue;				//the position of the reference point in the previous frame 


	std::vector<Layer> layers;							//vector of Layers


	src::severity_logger<severity_level> layerManagerLogger;
														//the logger for layerManager
};

