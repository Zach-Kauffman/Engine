#pragma once
#include "MenuSprite.h"
#include "MenuElement.h"

class MultiMenuSprite : public MenuElement, public NameSearchable			//This class is a named collection of menuSprites
{
public:
	MultiMenuSprite();														//constructor

	~MultiMenuSprite();														//destructor

	void setup();															//setup


	//inherited virtuals
	void update();															

	void update(MouseData& fmouseData);

	void draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition);

	void resetMD();


	void setCurrentMenuSpriteByName(std::string fname);						//sets which menuSprite to draw; can only draw one at a time

	void setCurrentMenuSpriteByIndex(int findex);							//same thing, but by index instead of by name


	void addMenuSprite(MenuSprite fmenuSprite, std::string fname);			//Adds a menusprite to the collection with a name

	void addMenuSprite(MenuSprite fmenuSprite, int fintname);				//same thing, but with an index that will be converted to a name -- useful in for loops


	MenuSprite* getMenuSpritePointerByName(std::string fname);				//returns a pointer to a menuSprite by name

	MenuSprite* getMenuSpritePointerByIndex(int findex);					//same, bu by index

private:

	std::vector<MenuSprite> spriteVector;									//the collection of MenuSprites

	int CMSIndex;															//current menuSprite index

};

