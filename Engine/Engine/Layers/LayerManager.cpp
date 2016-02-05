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

void  LayerManager::createAllLayers()
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->create();
	}
}




void LayerManager::addLayer()
{
	boost::shared_ptr<Layer> emptyLayer(new Layer);
	layers.push_back(emptyLayer);                                //makes and adds a new, empty Layer
}


void LayerManager::setLayerAmount(const int& amt)
{
	const unsigned int sizdif = amt - layers.size();
	if (amt < 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "There are already more than " << amt << " layers; removing layers in neither allowed or recommended; resizing layers failed.";
	}
	else if (amt == 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, INFO) << "There are already " << amt << " layers; resizing layers is meaningless.";
	}
	else
	{
		for (unsigned int i = 0; i < sizdif; i++)
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

	sf::Vector2f distance = *referencePoint - oldReferencePointValue;	//distance from the refernce point to where it used to be
	sf::RenderTexture* tmpRenderTex;




	for (int i = layers.size()-1; i>=0; i--)							//draw in reverse order -- makes intuitive sense: the first layer in the vector
																		//is the forwardmost layer, not backmost
	{
		layers[i]->interpretViewPos(distance);


		


		tmpRenderTex = layers[i]->getRenderTexture();


		tmpRenderTex->display();

		const sf::Texture& tmpTex = (tmpRenderTex->getTexture());			//get the texture from the layer

		sf::Sprite tmpSprite(tmpTex);									//set a sprite's texture as it

																		//move the sprite a portion of the distance to the old point where the portion
																		//is the scroll speed

		window.draw(tmpSprite);										//draw the new sprite

		tmpRenderTex->clear(sf::Color(0, 0, 0, 0));
	}

	oldReferencePointValue = *referencePoint;							//update the oldReferencePointValue
	

	if (dependentScrollLocking)
	{

		if (layers[indLayer]->getScrollLock().first == 2)
		{
			lockAll(0);
		}
		else
		{
			unlockAll(0);
		}

		if (layers[indLayer]->getScrollLock().second == 2)
		{
			lockAll(1);
		}
		else
		{
			unlockAll(1);
		}

	}



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

void LayerManager::setDepLocking(const bool& b, const unsigned int& indLay)
{
	dependentScrollLocking = b;
	indLayer = indLay;
	layers[indLayer]->setTrackLocking(true);
}


// private

void LayerManager::basicSetup()
{
	oldReferencePointValue = sf::Vector2f(0, 0);	//start the oldReferencePoint value at (0,0)
	layerManagerLogger = logger::getSLogger();		//setup the logger
	dependentScrollLocking = false;
	indLayer = 0;
}

void LayerManager::lockAll(const char& lockAxis)
{
	if (dependentScrollLocking)
	{
		for (unsigned int i = 0; i < layers.size(); i++)
		{
			if (layers[i]->getScrollBoundedness() && i != indLayer)
			{
				if (lockAxis == 'x' || lockAxis == 'X' || lockAxis == 0)
				{
					layers[i]->setScrollLock(2, 0);
				}
				else if (lockAxis == 'y' || lockAxis == 'Y' || lockAxis == 1)
				{
					layers[i]->setScrollLock(2, 1);
				}
			}
		}
	}

}

void LayerManager::unlockAll(const char& lockAxis)
{
	if (dependentScrollLocking)
	{
		for (unsigned int i = 0; i < layers.size(); i++)
		{
			if (layers[i]->getScrollBoundedness() && i != indLayer)
			{
				if (lockAxis == 'x' || lockAxis == 'X' || lockAxis == 0)
				{
					layers[i]->setScrollLock(1, 0);
				}
				else if (lockAxis == 'y' || lockAxis == 'Y' || lockAxis == 1)
				{
					layers[i]->setScrollLock(1, 1);
				}
			}
		}
	}
}