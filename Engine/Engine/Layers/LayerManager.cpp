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

void LayerManager::setDefaultSize(const sf::Vector2f& size)
{
	defaultSize = size;
}

void LayerManager::updateWindowSize(const sf::Vector2u size)
{
	std::vector<const double> bounds = { 0, 0, (double)size.x, (double)size.y };
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		setScrollBounds(bounds, i);
	}
}

void LayerManager::addLayer()
{
	boost::shared_ptr<Layer> emptyLayer(new Layer);

	if (!emptyLayer->getRenderTexture()->create(defaultSize.x, defaultSize.y))
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "failed to create layer number " << layers.size() + 1;
	}
	else
	{
		emptyLayer->getRenderTexture()->clear(sf::Color::Black);
		layers.push_back(emptyLayer);                                //makes and adds a new, empty Layer
	}
}

void LayerManager::addLayer(boost::shared_ptr<Layer> newLayer)
{
	newLayer->getRenderTexture()->clear(sf::Color::Black);
	layers.push_back(newLayer);		//adds an existant Layer
}

void LayerManager::setLayerAmount(const int& amt)
{
	const int sizDif = amt - layers.size();
	if (sizDif == 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, INFO) << "There already exist " << amt << " layers; setting the number of layers to this is meaningless.";
	}
	else if (sizDif < 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "There are more than " << amt << " layers; removing layers is neither reccomended nor allowed; setting the amount of layers failed.";
	}
	else
	{
		for (unsigned int i = 0; i < amt; i++)
		{
			addLayer();
		}
	}

}

unsigned int LayerManager::getLayerAmount()
{
	return layers.size();
}


void LayerManager::setScrollSpeeds(const sf::Vector2f& speed, const int& index)
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



void LayerManager::setScrollSpeeds(std::vector<const sf::Vector2f> scrollSpeeds)
{

	bool oddSpeed = false;												//if there is a speed < 0 or a speed > 1 or not
	
	resizeToMatchLayer(scrollSpeeds, "ScrollSpeeds");					//resizes the vector to have the same number of elements as the vector of layers. It also logs a warning

	for (unsigned int i = 0; i < layers.size(); i++)
	{

		const sf::Vector2f tmpSpeed = scrollSpeeds[i];					//record the speed of the corresponding scrollSpeed value

		layers[i]->setScrollSpeed(tmpSpeed);							//set the scrollSpeed of a layer to its previously determined matching speed

		if (!oddSpeed)
		{
			if (tmpSpeed.x < 0 || tmpSpeed.x  > 1 || tmpSpeed.y < 0 || tmpSpeed.y > 1)
			{
				oddSpeed = true;									//if a speed is < 0 or > 1, record that fact and don't record it again
			}
		}
		
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
	oldReferencePointValue = refPoint;
}



void LayerManager::draw(sf::RenderWindow& window)
{

	sf::Vector2f distance = oldReferencePointValue - *referencePoint;	//distance from the refernce point to where it used to be
	sf::RenderTexture* tmpRenderTex;
	for (int i = layers.size()-1; i>=0; i--)							//draw in reverse order -- makes intuitive sense: the first layer in the vector
																		//is the forwardmost layer, not backmost
	{
		tmpRenderTex = layers[i]->getRenderTexture();


		tmpRenderTex->display();
		const sf::Texture& tmpTex1 = (tmpRenderTex->getTexture());			//get the texture from the layer


		//layers[i]->clear(sf::Color(0, 0, 0, 0));						//clear the layer


		sf::Sprite tmpSprite1(tmpTex1);									//set a sprite's texture as it

//		tmpSprite.setPosition(oldReferencePointValue);
		tmpSprite1.move(layers[i]->getScrollDistance(distance));
																		//move the sprite a portion of the distance to the old point where the portion
																		//is the scroll speed


		window.draw(tmpSprite1);										//draw the new sprite

		tmpRenderTex->clear(sf::Color(0, 0, 0, 0));
	}

	//oldReferencePointValue = *referencePoint;							//update the oldReferencePointValue
	
}



void LayerManager::setScrollBounds(const double& nsBound, const unsigned int& boundIndex, const unsigned int& layerIndex)
{
	layers[layerIndex]->setScrollBounds(nsBound, boundIndex);
}

void LayerManager::setScrollBounds(std::vector<const double> nsBound, const unsigned int& layerIndex)
{
	layers[layerIndex]->setScrollBounds(nsBound);
}

void LayerManager::setScrollBounds(std::vector<std::vector<const double>> nsBoundVec)
{

	resizeToMatchLayer(nsBoundVec, "ScrollBounds");

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->setScrollBounds(nsBoundVec[i]);
	}
}


void LayerManager::setWindowCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner, const unsigned int& layerIndex)
{
	layers[layerIndex]->setExtremeCorners(fTLCorner, fBRCorner);
}

void LayerManager::setWindowCorners(std::vector<std::pair<const sf::Vector2f, const sf::Vector2f>> windowCornerVec)
{
	resizeToMatchLayer(windowCornerVec, "WindowCorners");

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->setExtremeCorners(windowCornerVec[i].first, windowCornerVec[i].second);
	}
}

// private

void LayerManager::basicSetup()
{
	oldReferencePointValue = sf::Vector2f(0, 0);	//start the oldReferencePoint value at (0,0)
	layerManagerLogger = logger::getSLogger();		//setup the logger
}
