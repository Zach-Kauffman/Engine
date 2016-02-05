#pragma once
#include "Layer.hpp"
#include "../Utility/Logger.hpp"
#include <vector>
#include "../Utility/Utilities.hpp"


class LayerManager										//holds and manages layers of graphics -- useful for parallax
{
public:

	LayerManager();										//constructor

	LayerManager(const int& amt);						//overloaded to dictate amount of layers at creation

	LayerManager(sf::Vector2f& refPoint);				//overloaded to specify the reference point at creation

	LayerManager(sf::Vector2f& refPoint, const int& amt);
														//overloaded to specify amount of layers and refernce point

	~LayerManager();									//nothing in destructor



	void setDefaultSize(const sf::Vector2f& s);			//sets new default size for window !!!!needs to be loaded from xml!!!

	void updateWindowSize(const sf::Vector2u size);						//updates dimensions of

	void createLayers();




	void addLayer();									//adds a new, empty layer

	void setLayerAmount(const int& amt);				//sets the amount of layers -- ideally used once only

	unsigned int getLayerAmount();




	void setScrollSpeed(const sf::Vector2f& speed, const int& index);
														//set the scroll speed of a particular layer

	void setScrollSpeed(std::vector<const sf::Vector2f> scrollSpeeds);
														//set the scroll speed of all layers; should start with 1 and descend


	boost::shared_ptr<Layer> getLayerPtr(const int& index);			
														//gets a shared pointer to a layer



	void setReferencePoint(sf::Vector2f& refPoint);		//sets the point that the layers will center on



	void draw(sf::RenderWindow& window);				//draws all of the layers


	
	void setScrollBounds(const double& bound, const unsigned int& boundIndex, const unsigned int& layerIndex);
	
	void setScrollBounds(std::vector<const double> bounds, const unsigned int& layerIndex);

	void setScrollBounds(std::vector<std::vector<const double>> boundVec);



	void setCorners(const sf::Vector2f& TLCorner, const sf::Vector2f& BRCorner, const unsigned int& layerIndex);

	void setCorners(std::vector<std::pair<const sf::Vector2f, const sf::Vector2f>> cornerVec);

	void setDependentLocking(const bool& b, const unsigned int& indLay);

private:

	void basicSetup();									//setup called in every constructor

	void lockAll(const char& lockAxis);

	void unlockAll(const char& lockAxis);



	template<class T> 
	void resizeToMatchLayer(std::vector<T>& vec, const std::string& name)
	{
		if (vec.size() != layers.size())
		{
			BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The amount of input " << name << " does not match the amount of layers. It was resized to match.";
			vec.resize(layers.size());
		}
	}
	

	bool dependentScrollLocking;

	unsigned int indLayer;

	sf::Vector2f defaultSize;

	sf::Vector2f* referencePoint;						//The point the LayerManager is centered on

	sf::Vector2f oldReferencePointValue;				//the position of the reference point in the previous frame 


	std::vector<boost::shared_ptr<Layer>> layers;		//vector of shared pointers to Layers -- has to be dynamically stored
														//because renderTexture is Noncopyable


	src::severity_logger<severity_level> layerManagerLogger;	//the logger for layerManager

	
};

