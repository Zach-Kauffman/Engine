#include "LayerManager.hpp"


// public


//constructors---

LayerManager::LayerManager()
{
	basicSetup();
}

LayerManager::LayerManager(const int& amt)
{
	basicSetup();
	setLayerAmount(amt);
}

LayerManager::LayerManager(sf::Vector2f& refPoint)
{
	basicSetup();
	setReferencePoint(refPoint);
}

LayerManager::LayerManager(sf::Vector2f& refPoint, const int& amt)
{
	basicSetup();
	setLayerAmount(amt);
	setReferencePoint(refPoint);
}

//---done

LayerManager::~LayerManager()
{
}



void LayerManager::addEmptyLayer()
{
	boost::shared_ptr<Layer> emptyLayer(new Layer);
	layers.push_back(emptyLayer);								//makes and adds a new, empty Layer
}

void LayerManager::addLayer(boost::shared_ptr<Layer> newLayer)
{
	layers.push_back(newLayer);		//adds an existant Layer
}

void LayerManager::setLayerAmount(const int& amt)
{
	layers.resize(amt);											//resize the Layer vector to the desired size
}



void LayerManager::setScrollSpeed(const sf::Vector2f& speed, const int& index)
{
	if (index >= 0 && index < layers.size())
	{
		layers[index]->setScrollSpeed(speed);	//if the index is valid, set the scrollSpeed

		if (speed.x < 0 || speed.x > 1 || speed.y < 0 || speed.y > 1)
		{
			BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The desired scroll speed is not between 0 and 1 inclusive. It will still work but will look odd.";
												//if the speed is not between 0 and 1, log a warning
		}
	}
	else
	{
		BOOST_LOG_SEV(layerManagerLogger, ERROR) << "There do not exist at least " << index + 1 << " layers yet; Accessing spot " << index << " failed.";
												//if it's a bad index, log an error
	}
}



void LayerManager::setAllScrollSpeeds(const std::vector<const sf::Vector2f>& scrollSpeeds)
{
	unsigned int ss_siz = scrollSpeeds.size() - 1;					//(size of scrollSpeeds) - 1

	bool oddSpeed = false;											//if there is a speed < 0 or a speed > 1 or not
	

	for (unsigned int i = 0; i < layers.size(); i++)
	{

		const sf::Vector2f tmpSpeed = scrollSpeeds[util::uimin(i, ss_siz)];
																	//record the speed of the corresponding scrollSpeed value
																	//If the scrollSpeed vec is too small for some reason, the last element will
																	//be reused

		layers[i]->setScrollSpeed(tmpSpeed);							//set the scrollSpeed of a layer to its previously determined matching speed

		if (!oddSpeed)
		{
			if (tmpSpeed.x < 0 || tmpSpeed.x  > 1 || tmpSpeed.y < 0 || tmpSpeed.y > 1)
			{
				oddSpeed = true;									//if a speed is < 0 or > 1, record that fact and don't record it again
			}
		}
		
	}

	if (ss_siz + 1 != layers.size())
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The amount of input scrollSpeeds does not match the amount of layers.";
																	//if the scrollSpeed Vector had a different size than the layers vector, log a warning
	}
	if (oddSpeed)
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "An odd scrollSpeed was detected. It was either < 0 or > 1. It will still work, however.";
																	//if there was an odd scrollSpeed, log a warning
	}
}



boost::shared_ptr<Layer> LayerManager::getLayerPointer(const int& index)
{
	return 	layers[index];											//return the memory location of the desired layer
}



void LayerManager::setReferencePoint(sf::Vector2f& refPoint)
{
	referencePoint = &refPoint;										//set the reference point
}



void LayerManager::draw(sf::RenderWindow& window)
{

	sf::Vector2f distance = oldReferencePointValue - *referencePoint;	//distance from the refernce point to where it used to be
		
	for (unsigned int i = layers.size(); i > 0; --i)					//draw in reverse order -- makes intuitive sense: the first layer in the vector
																		//is the forwardmost layer, not backmost
	{
		const sf::Texture& tmpTex = layers[i]->getTexture();				//get the texture from the layer

		sf::Sprite tmpSprite(tmpTex);									//set a sprite's texture as it

		tmpSprite.move(layers[i]->getScrollSpeed().x * distance.x, layers[i]->getScrollSpeed().y * distance.y);
																		//move the sprite a portion of the distance to the old point where the portion
																		//is the scroll speed

		window.draw(tmpSprite);											//draw the sprite					
	}

	oldReferencePointValue = *referencePoint;							//update the oldReferencePointValue

}


// private

void LayerManager::basicSetup()
{
	oldReferencePointValue = sf::Vector2f(0, 0);	//start the oldReferencePoint value at (0,0)
	layerManagerLogger = logger::getSLogger();		//setup the logger
}
