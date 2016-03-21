#include "SingleTextBox.h"




SingleTextBox::SingleTextBox()
{

	requiresMouseData = false;					//does not require mouse data

	isHidden = false;							//draw it by default

	resetsOnMD = false;							//does not reset on menu deactivation


}



SingleTextBox::SingleTextBox(sf::Vector2f fposition, const sf::Font* const ffont, std::string fstring, int ffontsize, double fmaxwidth, sf::Color fcolor)
{
	requiresMouseData = false;					//same stuff

	isHidden = false;

	resetsOnMD = false;

	setup(fposition, ffont, fstring, ffontsize, fmaxwidth, fcolor);		//setup


}



SingleTextBox::~SingleTextBox()
{
}




void SingleTextBox::setup(sf::Vector2f fposition, const sf::Font* const ffont, std::string fstring, int ffontsize, double fmaxwidth, sf::Color fcolor)
{

	position = fposition;						//set position

	characterSize = ffontsize;					//set char size

	textColor = fcolor;							//set text color
		
	width = fmaxwidth;							//set width

	drawString = fstring;						//set drawString



	textBody.setFont(*ffont);					//set the font to the text

	textBody.setString(fstring);				//set the text to draw the given string

	textBody.setCharacterSize(ffontsize);		//set the char size

	wrapText();									//wrap the text

	textBody.setColor(fcolor);					//set the color



												//set it equal to the dimensions of the text box

	correctPosition();							//corrects the text's position

}




void SingleTextBox::update()					//empty
{ 

}




void SingleTextBox::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)	//empty
{

}



void SingleTextBox::draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition)
{
	position += drawPosition;					//add the draw position to make things relative

	textBody.move(position);					//move the textBody

	frenderwindow.draw(textBody);				//draw it

	textBody.move(-position);					//move it back

	position -= drawPosition;					//subtract the draw position
}



void SingleTextBox::resetMD()					//doesn't reseton Menu deactivation
{

}



sf::Vector2f SingleTextBox::getGlobalDimensions()
{
	return sf::Vector2f(textBody.getGlobalBounds().width, textBody.getGlobalBounds().height);
}

sf::Vector2f SingleTextBox::getLocalDimensions()
{
	return sf::Vector2f(textBody.getLocalBounds().width, textBody.getLocalBounds().height);
}

sf::Vector2f SingleTextBox::getLetterPosition(const unsigned int& index)
{
	return textBody.findCharacterPos(index);
}

sf::Vector2f SingleTextBox::getLastLetterPosition()
{
	return textBody.findCharacterPos(drawString.size() + 1);
}

void SingleTextBox::setTextString(std::string fstring)	//sets the string you want to draw
{
	textBody.setString(fstring);						//set the string
	drawString = fstring;

	wrapText();											//wrap the text
	correctPosition();
}



void SingleTextBox::setTextColor(sf::Color fcolor)		//set the color of the text
{
	textBody.setColor(fcolor);							//yep, do it
}



void SingleTextBox::setFontSize(int fsize)				//set the font size in pixels
{
	textBody.setCharacterSize(fsize);					//set the size of the characters
		
	wrapText();											//wrap the text

	correctPosition();
}


//private

void SingleTextBox::wrapText()				//wraps the string around a margin
{
	std::string searchString;

	for (unsigned int i = 0; i < drawString.size(); i++)	
	{
		searchString = drawString[i];
		if (searchString == "\n")
		{
			drawString[i] = ' ';			//first, change all "\n"s to spaces -- that is make the text "one line long"
		}
	}


	

	int spaceIndex;							//keeps track of where the last space was

	char letter;							//the current letter

	std::string word = "";					//the current word

	std::string line = "";					//the current line of text

	std::string transline = "";				//the current line of text that is used to test the width of the string

	std::string rtstr = "";					//the string to return
		
	bool notFirstWord = false;				//true if the current word is not the first word

	bool notFirstLine = false;				//true if the current line is not the first line

	for (unsigned int i = 0; i <= drawString.size(); i++)	//go though the string-to-be-drawn + 1 extra space...
	{

		if (i == drawString.size())
		{
			letter = ' ';					//at the space 'after' the end, we call it a space
		}
		else
		{
			letter = drawString[i];			//otherwise its jsut the index of tthe drawString
		}
		


		if (letter == ' ')					//if a space is found
		{
			if (notFirstWord)				//if it's not the first space/word
			{
				transline += ' ';			//add a space to the beginning of the word
			}

			transline += word;				//then add the word onto the testing line

			if (getDimensionsOfString(transline).x > width)	//if the width would be greater than acceptable,
			{
				if (notFirstLine)			//if its not the first line
				{
					rtstr += "\n";			//tack a newline on the beginning
				}

				rtstr += line;				//add the line onto the finished string

				notFirstWord = false;		//since it is going ot be a new line on the next teration, it is going to be the first word of that line

				if (!notFirstLine)
				{
					notFirstLine = true;	//it won't be the first line anymore after the first line
				}


				line = "";					//revert the line and testing line back to ""
				transline = "";	

				i = spaceIndex;				//revert the index back to the last space
	
			}

			else							//if the width of the text would be fine, instead
			{
				line = transline;			//replace the current line with the testing line -- it passed the test

				notFirstWord = true;		//it's no longer the first word

				spaceIndex = i;				//the last space was at the current index

				if (i == drawString.size())	//if the iteration is one greater than the possible indices in the string (in the case of "finishing early")
				{

					if (notFirstLine)		//if its not hte first line
					{
						rtstr += "\n";		//tack on a newline at the beginning
					}

					rtstr += line;			//throw on the current line
				}

			}
			
			word = "";						//reset the word to "" if the letetr was a space
	
		}

		else								//if the letter wasn't a space
		{
			word += letter;					//throw it on the current word
		}

	}

	textBody.setString(rtstr);				//set the drawn string to the finished string
}



sf::Vector2f SingleTextBox::getDimensionsOfString(std::string fstr)	//gets the dimensions of a hypothetical string given the other conditions of the textBox
{

	sf::Text tmpText;												//make a temporary text

	tmpText.setFont(*textBody.getFont());							//set it up just like the texBox's Text

	tmpText.setCharacterSize(characterSize);

	tmpText.setString(fstr);										//set the string to be the hypothetical one

	return sf::Vector2f(tmpText.getGlobalBounds().width, tmpText.getGlobalBounds().height);
																	//return the dimensions of the Text

}



void SingleTextBox::correctPosition()							//corrects the position of the text because text is dumb
{

	sf::Vector2f tempDimensions;							//make temp dimensions

	tempDimensions = sf::Vector2f(textBody.getLocalBounds().width, textBody.getLocalBounds().height);


	textBody.setOrigin(tempDimensions.x / 2, tempDimensions.y / 2);
																//set the origin in the center

	textBody.setPosition(0,0);									//set the position at 0,0 by default



	double maxHeight = 0;										//declare maxHeight and a temporary string	

	std::string tmpString;

	for (unsigned int i = 0; i < drawString.size(); i++)		//go through the drawString
	{
		tmpString = drawString[i];								//set tmep string equal to the char at the indexth point in the drawString

		if (tmpString == "\n")									
		{
			break;												//if it's a newline, stop
		}

		else if (getDimensionsOfString(tmpString).y > maxHeight)	//otherwise, if the height of the letter is bigger than the maxHeight,
		{
			maxHeight = getDimensionsOfString(tmpString).y;		//make the maxHeight the current letter's height
		}
	}

	textBody.move(sf::Vector2f(0, - maxHeight / 2));			//move the textBody up by half the maxHeight -- don't ask why
}

