#include "MultiMenuSprite.h"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



/*------------------------------------------------------------------------------------
---------------------------------constructor------------------------------------------
------------------------------------------------------------------------------------*/
MultiMenuSprite::MultiMenuSprite()								//constructor
{
	setVectorSize(1);											//There is only one name map

	requiresMouseData = false;									//it does not require mouse data

	isHidden = false;											//draws by default			

	resetsOnMD = false;											//does  not reset on menu deactvation
}



/*------------------------------------------------------------------------------------
---------------------------------destructor-------------------------------------------
------------------------------------------------------------------------------------*/
MultiMenuSprite::~MultiMenuSprite()
{
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
---------------------------------update-----------------------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::update()
{
	for (unsigned int i = 0; i < spriteVector.size(); i++)		//update all of the menuSprites
	{
		spriteVector[i].update();
	}
}



/*------------------------------------------------------------------------------------
------------------------------update-with-mouseData-----------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::update(MouseData& fmouseData)
{
	for (unsigned int i = 0; i < spriteVector.size(); i++)		//update all of the menuSprites
	{
		spriteVector[i].update(fmouseData);
	}
}




//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
---------------------------------draw-------------------------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition)
{
	position += drawPosition;								//add the draw position to make position relative

	for (unsigned int i = 0; i < spriteVector.size(); i++)
	{
		if (!spriteVector[i].getIsHidden())
		{
			spriteVector[i].draw(frenderwindow, position);	//draw all the unhidden menuSprites
		}
		
	}

	position -= drawPosition;								//subtract draw position because it was added
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
---------------------------------resetMD----------------------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::resetMD()								//empty
{

}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------setCurrentMenuSpriteByName-----------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::setCurrentMenuSpriteByName(std::string fname)	//changes the current menu sprite to another by name
{

	if (CMSIndex >= 0)
	{
		spriteVector[CMSIndex].hide();								//hide the old menuSprite ; in this case, doesn't actually do anything; just is for consistency
	}

	CMSIndex = ntoi(fname);											//set the current menu sprite equal to the index associated with the name

	spriteVector[CMSIndex].unhide();								//unhide the one that was named; again, doesn't matter

}


/*------------------------------------------------------------------------------------
-------------------------setCurrentMenuSpriteByIndex----------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::setCurrentMenuSpriteByIndex(int findex)		//same thing as above but by index
{
	if (CMSIndex >= 0)
	{
		spriteVector[CMSIndex].hide();
	}

	CMSIndex = findex;

	spriteVector[CMSIndex].unhide();
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------addMenuSprite(Name)------------------------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::addMenuSprite(MenuSprite fmenuSprite, std::string fname)	//adds a named menuSprite
{
	if (spriteVector.size() > 0)
	{
		fmenuSprite.hide();														//hide the menu sprite if it's not the first
	}
	else
	{
		CMSIndex = 0;															//only change the CMSIndex if it is the first
	}

	spriteVector.push_back(fmenuSprite);										//push it to the vector

	addName(fname, spriteVector.size() - 1);									//add the name

}



/*------------------------------------------------------------------------------------
-------------------------addMenuSprite(intedName)-------------------------------------
------------------------------------------------------------------------------------*/
void MultiMenuSprite::addMenuSprite(MenuSprite fmenuSprite, int fintname)		//adds a named (based on an int this time) menusprite -- essetially same thing
{
	if (spriteVector.size() > 0)
	{
		fmenuSprite.hide();
	}
	else
	{
		CMSIndex = 0;
	}

	spriteVector.push_back(fmenuSprite);

	addName(fintname, spriteVector.size() - 1);
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------getMenuSpritePointerByName-----------------------------------
------------------------------------------------------------------------------------*/
MenuSprite* MultiMenuSprite::getMenuSpritePointerByName(std::string fname)		//get a pointer to a menuSprite by name
{
	MenuSprite* tmpSprite = &spriteVector[ntoi(fname)];							//make one

	return tmpSprite;															//return it
}


/*------------------------------------------------------------------------------------
-------------------------getMenuSpritePointerByIndex----------------------------------
------------------------------------------------------------------------------------*/
MenuSprite* MultiMenuSprite::getMenuSpritePointerByIndex(int findex)			//same thing, but by index
{
	MenuSprite* tmpSprite = &spriteVector[findex];
	return tmpSprite;
}

//----------------------------------------------------------------------------------------------------------------------------***************************