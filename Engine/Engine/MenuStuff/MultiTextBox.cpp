#include "MultiTextBox.h"


MultiTextBox::MultiTextBox()
{
	setVectorSize(1);										//only one name map

	requiresMouseData = false;								//does not require mouse data

	isHidden = false;										//will be drawn

	resetsOnMD = false;										//does not reset on menu dectivation

	CTBIndex = -1;											//th current TextBox index starts as -1

}


MultiTextBox::~MultiTextBox()
{

}



void MultiTextBox::update()									//update
{
	for (unsigned int i = 0; i < textBoxVector.size(); i++)
	{
		textBoxVector[i].update();							//update every textBox
	}
}


void MultiTextBox::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)			//update with mouse data
{
	for (unsigned int i = 0; i < textBoxVector.size(); i++)
	{
		textBoxVector[i].update(fmouseData, typedChar, fkeyData);				//update every textBox with mouse data
	}
}


void MultiTextBox::draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition)
{
	position += drawPosition;								//add the draw position to make textBoxes' positions relative

	if (!textBoxVector[CTBIndex].getIsHidden())
	{
		textBoxVector[CTBIndex].draw(frenderwindow, position);	
															// if the current TextBox isn't hidden, draw it
	}


	position -= drawPosition;								//take away the draw position because it was added
}



void MultiTextBox::resetMD()								//empty
{

}



void MultiTextBox::setCurrentTextBoxByName(std::string fname)	//set the current textBox to naother by name
{
	if (CTBIndex >= 0)
	{
		textBoxVector[CTBIndex].hide();						//hide the old textBox; doesnt really matter; just for consistency
	}

	CTBIndex = ntoi(fname);									//most important: the current TextBox index is the index associated with the name

	textBoxVector[CTBIndex].unhide();						//unhide the one that was named; again, doesn't matter


}



void MultiTextBox::setCurrentTextBoxByIndex(int findex)		//set the textbox being drawn by index 
{

	if (CTBIndex >= 0)
	{
		textBoxVector[CTBIndex].hide();
	}

	CTBIndex = findex;

	textBoxVector[CTBIndex].unhide();						//unhide the one that was named
}


void MultiTextBox::addTextBox(SingleTextBox fsingleTextBox, std::string fname) 
{
	if (textBoxVector.size() > 0)
	{
		fsingleTextBox.hide();								//hide the textBox if it's not the first
		
	}
	else
	{	
		CTBIndex = 0;										//only change the CTBIndex if it is the first
	}
	
	textBoxVector.push_back(fsingleTextBox);				//add it to the collection

	addName(fname, textBoxVector.size() - 1);				// add the name
}


void MultiTextBox::addTextBox(SingleTextBox fsingleTextBox, int finame) 
															//same thing, essentially as the previous one
{
	if (textBoxVector.size() > 0)
	{
		fsingleTextBox.hide();		

	}
	else
	{
		CTBIndex = 0;				
	}

	textBoxVector.push_back(fsingleTextBox);				

	addName(finame, textBoxVector.size() - 1);				// add the inted name
}



SingleTextBox* MultiTextBox::getTextBoxPointerByName(std::string fname)
{
	SingleTextBox* tmpTextBox = &textBoxVector[ntoi(fname)];	//make the pointer

	return tmpTextBox;											//return it
}



SingleTextBox* MultiTextBox::getTextBoxPointerByIndex(int findex)
{
	SingleTextBox* tmpTextBox = &textBoxVector[findex];			//make the pointer

	return tmpTextBox;											//return it
}

