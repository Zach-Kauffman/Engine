#include "AppSprite.h"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



/*------------------------------------------------------------------------------------
----------------------------Argumentless-constructor----------------------------------
------------------------------------------------------------------------------------*/
AppSprite::AppSprite()
{
	rotation = 0;
	position = sf::Vector2f(0, 0);
}



/*------------------------------------------------------------------------------------
--------------------------Multi-Argument-constructor1---------------------------------
------------------------------------------------------------------------------------*/
AppSprite::AppSprite(const sf::Texture* ftexture, sf::Vector2f fposition, sf::Vector2f fsize, double frot)
{
	rotation = frot;

	position = sf::Vector2f(0, 0);

	setup(ftexture, position, fsize, frot);		//setup	
}


/*------------------------------------------------------------------------------------
--------------------------Multi-Argument-constructor2---------------------------------
------------------------------------------------------------------------------------*/
AppSprite::AppSprite(const sf::Texture* ftexture, sf::Vector2f fTL, sf::Vector2f fBR)
{
	sf::Vector2f tposition = fTL + fBR;
	tposition.x /= 2.00;
	tposition.y /= 2.00;


	sf::Vector2f dimensions(fabs(fBR.x - fTL.x), fabs(fBR.y - fTL.y));

	setup(ftexture, tposition, dimensions, 0);
}



/*------------------------------------------------------------------------------------
--------------------------------destructor--------------------------------------------
------------------------------------------------------------------------------------*/
AppSprite::~AppSprite()
{

}



/*------------------------------------------------------------------------------------
---------------------------------setup------------------------------------------------
------------------------------------------------------------------------------------*/
void AppSprite::setup(const sf::Texture* ftexture, sf::Vector2f fposition, sf::Vector2f fsize, double frot)
{
	position = fposition;				//position is set

	rotation = frot;

	appImage.setTexture(*ftexture);	//set the texture of the Sprite

	sf::Vector2f tempDimensions(sf::Vector2f(appImage.getLocalBounds().width, appImage.getLocalBounds().height));
	//make temporary helper dimensions

	appImage.setOrigin(tempDimensions.x / 2, tempDimensions.y / 2);
	//set the origin in the center of the temp dimensions

	appImage.setScale(fsize.x / tempDimensions.x, fsize.y / tempDimensions.y);
	//set the scale such that it is the correct size

	appImage.setPosition(0, 0);		//position is set (relatively) to (0,0)

	appImage.setRotation(frot);
}



//----------------------------------------------------------------------------------------------------------------------------***************************


void AppSprite::move(sf::Vector2f fdisp)
{
	position += fdisp;
}

void AppSprite::setPosition(sf::Vector2f fpos)
{
	position = fpos;
}


void AppSprite::rotate(double frot)
{
	appImage.rotate(frot);
}

void AppSprite::setRotation(double frot)
{
	appImage.setRotation(frot);
}
//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
---------------------------------draw------------------------------------------------
------------------------------------------------------------------------------------*/
void AppSprite::draw(sf::RenderWindow& frenderWindow, sf::Vector2f drawPosition)
{

	position += drawPosition;		//add the drawPosition  to make position relative



	appImage.move(position);		//move the appImage

	frenderWindow.draw(appImage);	//draw the appImage

	appImage.move(-position);		//move the appImage back



	position -= drawPosition;		//subtract the drawPosition because we added it

}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
---------------------------------getGlobalDimensions----------------------------------
------------------------------------------------------------------------------------*/
sf::Vector2f AppSprite::getGlobalDimensions()													//all this function does is literally return the global
//dimensions of the Sprite
{
	return sf::Vector2f(appImage.getGlobalBounds().width, appImage.getGlobalBounds().height);	//yep
}



/*------------------------------------------------------------------------------------
---------------------------------getLocalDimensions-----------------------------------
------------------------------------------------------------------------------------*/
sf::Vector2f AppSprite::getLocalDimensions()													//same thing as above, except the dimensions are local
{
	return sf::Vector2f(appImage.getLocalBounds().width, appImage.getLocalBounds().height);
}


//----------------------------------------------------------------------------------------------------------------------------***************************