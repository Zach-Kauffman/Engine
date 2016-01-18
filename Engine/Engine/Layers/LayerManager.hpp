#pragma once
#include "Layer.hpp"
#include "../Logger.hpp"
#include <vector>
#include "../Utilities.hpp"


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

	void addLayer(boost::shared_ptr<Layer> newLayer);	//adds an existant layer

	void setLayerAmount(const int& amt);				//sets the amount of layers -- ideally used once only

	void setScrollSpeeds(const sf::Vector2f& speed, const int& index);
														//set the scroll speed of a particular layer


	void setScrollSpeeds(std::vector<const sf::Vector2f> scrollSpeeds);
														//set the scroll speed of all layers; should start with 1 and descend

	boost::shared_ptr<Layer> getLayerPointer(const int& index);			
														//gets a shared pointer to a layer


	void setReferencePoint(sf::Vector2f& refPoint);		//sets the point that the layers will center on


	void draw(sf::RenderWindow& window);				//draws all of the layers


	
	void setScrollBounds(const double& nsBound, const unsigned int& boundIndex, const unsigned int& layerIndex);

	void setScrollBounds(std::vector<const double> nsBound, const unsigned int& layerIndex);

	void setScrollBounds(std::vector<std::vector<const double>> nsBoundVec);


	void setWindowCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner, const unsigned int& layerIndex);

	void setWindowCorners(std::vector<std::pair<const sf::Vector2f, const sf::Vector2f>> windowCornerVec);


private:

	void basicSetup();									//setup called in every constructor

	template<class T> 
	void resizeToMatchLayer(std::vector<T>& vec, const std::string& name)
	{
		if (vec.size() != layers.size())
		{
			BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The amount of input " << name << " does not match the amount of layers. It was resized to match.";
			vec.resize(layers.size());
		}
	}
	


	sf::Vector2f* referencePoint;						//The point the LayerManager is centered on

	sf::Vector2f oldReferencePointValue;				//the position of the reference point in the previous frame 


	std::vector<boost::shared_ptr<Layer>> layers;		//vector of shared pointers to Layers -- has to be dynamically stored
														//because renderTexture is Noncopyable


	src::severity_logger<severity_level> layerManagerLogger;
														//the logger for layerManager
};

