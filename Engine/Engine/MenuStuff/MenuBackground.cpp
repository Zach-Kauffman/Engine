#include "MenuBackground.h"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



/*------------------------------------------------------------------------------------
-------------------Constructor--------------------------------------------------------
------------------------------------------------------------------------------------*/
MenuBackground::MenuBackground(	sf::Vector2f fposition,
								sf::Texture* ftexture,								
								sf::Vector2f fspriteSize)						//position, texture, and spriteSize define a menubackground
{
	position = fposition;														//set the position to the desired position

	requiresMouseData = 0;														//menuBG does NOT require mouse data

	isHidden = false;															//menuBG is drawn usually

	resetsOnMD = false;															//menuBG does not need to reset




	sf::Vector2f tempDimensions;												//declare temporary helper dimensions

	backgroundSprite.setTexture(*ftexture);										//set the texture to the desired one

	tempDimensions = sf::Vector2f(	backgroundSprite.getLocalBounds().width,
									backgroundSprite.getLocalBounds().height);	//set the temporary hleper dimensions
	
	backgroundSprite.setOrigin(tempDimensions.x / 2, tempDimensions.y / 2);		//set the origin in the center of the rectangle

	backgroundSprite.setScale(	fspriteSize.x / tempDimensions.x,
								fspriteSize.y / tempDimensions.y);				//set the scale such that the new size is the desired size

	backgroundSprite.setPosition(0, 0);											//set the position of the sprite at (0,0) relatively
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------update-------------------------------------------------------------
------------------------------------------------------------------------------------*/
void MenuBackground::update()													//empty; inherited virtual
{

}



/*------------------------------------------------------------------------------------
-------------------updatewithMouseData------------------------------------------------
------------------------------------------------------------------------------------*/
void MenuBackground::update(MouseData& fmouseData)								//empty; inherited virtual
{

}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
------------------------------draw---------------------------------------------------
------------------------------------------------------------------------------------*/
void MenuBackground::draw(	sf::RenderWindow& frenderWindow,
							sf::Vector2f drawPosition)							//draws the Sprite
{
	position += drawPosition;													//add the draw position to the position of the menuBG



	backgroundSprite.move(position);											//move the sprite by the position of the menuBG

	frenderWindow.draw(backgroundSprite);										//draw it

	backgroundSprite.move(-position);											//move it back



	position -= drawPosition;													//subtract the draw position because we added it.

}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-----------------------------ResetMd--------------------------------------------------
------------------------------------------------------------------------------------*/
void MenuBackground::resetMD()
{

}


//----------------------------------------------------------------------------------------------------------------------------***************************
