#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities.hpp"

class Layer : public sf::RenderTexture					//Layer is a RenderTexture that can have parallax added to it; it is a "small" class
														//because it is a light wrapper of RenderTexture
{

public:

	Layer();											//constructor and destructor are empty
	~Layer();

	void setScrollSpeed(const sf::Vector2f& fspeed);	//set the scrolling speed of the layer; should be pairs of numbers bewtween 0 and 1 inclusive

	sf::Vector2f getScrollSpeed();						//get scroll speed



	void setScrollBounds(const double& nsBound, const unsigned int& index);
														//sets a specific scrollBound


	void setScrollBounds(std::vector<const double> nsBound);	//set all scrollBounds

	double getScrollBound(const unsigned int& index);	//gets a scroll bound by index


	void setScrollBoundedness(const bool& nscrollBounded);

	bool getScrollBoundedness();




	void setInitTracking(const sf::Vector2f& inTracking);

	sf::Vector2f getScrollDistance(const sf::Vector2f& scrollDist);




private:

	sf::Vector2f boundScrollTracker();

	sf::Vector2f scrollSpeed;							//the fraction of the "normal" scroll speed at which a layer will scroll; a layer with
														//.5 scroll speed will scroll half as quickly as a layer with 1 scroll speed; a layer with 0
														//scroll speed will be stationary.

	double scrollBounds[4];								//does not work yet,
														//the purpose is that a layer should not be able to scroll forever. see http://imgur.com/SzH03Ju for a lack of scroll bounds.

	bool scrollBounded;									//true if the layer has active scrolling bounds.


	sf::Vector2f scrollTracker;							//keeps track of the scrolling

	

	enum boundPositions { Top = 0, Left, Bottom, Right };
};

