#pragma once
#include <SFML\Graphics.hpp>
#include "..\Input\MouseData.hpp"

class AppSprite																	//This class is a more useful sprite
{

public:

	AppSprite();																	//0-argument constructor

	AppSprite(const sf::Texture* ftexture, sf::Vector2f fposition, sf::Vector2f fsize, double frot);	//constructor with all elements

	AppSprite(const sf::Texture* ftexture, sf::Vector2f fTL, sf::Vector2f fBR);

	~AppSprite();																	//destructor


	void setup(const sf::Texture* ftexture, sf::Vector2f fposition, sf::Vector2f fsize, double frot);	//sets up the MenuSprite
	

	void move(sf::Vector2f fdisp);

	void setPosition(sf::Vector2f fpos);

	
	void rotate(double frot);

	void setRotation(double frot);


	void draw(sf::RenderWindow& frenderWindow, sf::Vector2f drawPosition);




	sf::Vector2f getGlobalDimensions();												//returns the dimensions of the AppSprite globally

	sf::Vector2f getLocalDimensions();												//returns the dimensions of the AppSprite locally

private:

	sf::Vector2f position;

	sf::Sprite appImage;															//the Sprite that AppSprite	is just a wrappedd version of.

	double rotation;

};

