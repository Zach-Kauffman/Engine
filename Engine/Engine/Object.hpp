#pragma once

//sfml includes
#include "SFML/Graphics.hpp"

class Object	//virtual class template for basic Object type
{
public:
	Object();
	~Object();

	virtual void draw(sf::RenderTexture& renderTarget) = 0;		//renders object to given sf::RenderTexture&
	virtual void update() = 0;

	virtual void load() = 0;
	virtual void write() = 0;

private:
	int identifactionTag;	//unique ID for instance of object
	bool isActive;			//wether or not the object will be drawn/updated etc
};