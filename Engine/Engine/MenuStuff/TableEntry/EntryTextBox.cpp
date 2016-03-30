#include "EntryTextBox.hpp"


EntryTextBox::EntryTextBox()
{
	//strTracker = "";
	//*entryString = "a";

	isActive = false;

	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	

}


EntryTextBox::~EntryTextBox()
{
}


EntryTextBox::EntryTextBox(	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color& fcolor,
							sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
							)
{

	isActive = false;

	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	

	setup(ffont, ffontsize, fcolor, bgTex, bgSiz, barTex, fpos, indent);

}

void EntryTextBox::setup(	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color& fcolor,
							sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
							)
{
	background.setup(bgTex, sf::Vector2f(0,0), bgSiz);
	position = fpos;
	textBox.setup(sf::Vector2f(0, 0), ffont, "", ffontsize, bgSiz.x - 2 * indent, fcolor);
	textBar.setup(barTex, sf::Vector2f(0, 0), sf::Vector2f(bgSiz.x / 40.0f, bgSiz.y - 2 * indent));
}


void EntryTextBox::setEntryString(std::string& estr)
{
	entryString = &estr;
}
//std::string EntryTextBox::getEntryString()
//{
//	return entryString;
//}


void EntryTextBox::update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData)
{
	setActivity(fmouseData);


	if (isActive)
	{
		if (typedChar != '\0')
		{
			buildEntryString(typedChar);
		}
		textBox.setTextString(*entryString);
	}
	setBarPos();



}

void EntryTextBox::draw(sf::RenderWindow& window, sf::Vector2f drawPos)
{
	if (lastDrawPos != drawPos)
	{
		lastDrawPos = drawPos;
	}
	
	position += drawPos;

	background.draw(window, position);
	textBox.draw(window, position);


	if (isActive)
	{
		textBar.draw(window, position);
	}

	



	position -= drawPos;
}

//private

void EntryTextBox::buildEntryString(const char& typedChar)
{
	

	if (isActive )
	{
		if (typedChar != 0)
		{
			if (typedChar == '\b')
			{
				if (entryString->size())
				{
					entryString->erase(entryString->end() - 1);
				}
			}
			else
			{
				*entryString += typedChar;
			}
		}
		
	}


}


void EntryTextBox::setActivity(MouseData& mdata)
{
	sf::Vector2f mpos = mdata.getPosition() - lastDrawPos - position;
	bool clicked = (mdata.getLeftData() == MouseData::Hit);
	/*
	std::cout << mdata.getPosition().x << ", " << mdata.getPosition().y << std::endl;
	std::cout << lastDrawPos.x << ", " << lastDrawPos.y << std::endl;
	std::cout << mpos.x << ", " << mpos.y << std::endl;
	std::cout << background.getGlobalBounds().left << ", " << background.getGlobalBounds().top << std::endl;
	*/
	const sf::Vector2f tlc = sf::Vector2f(	background.getPosition().x - background.getGlobalDimensions().x / 2.0f,
											background.getPosition().y - background.getGlobalDimensions().y / 2.0f
											);

	const sf::Vector2f brc = sf::Vector2f(	background.getPosition().x + background.getGlobalDimensions().x / 2.0f,
											background.getPosition().y + background.getGlobalDimensions().y / 2.0f
											);

	if (mpos.x < brc.x && mpos.x > tlc.x && mpos.y < brc.y && mpos.y > tlc.y )
	{
		if (clicked)
		{
			isActive = true;
		}

	}
	else
	{
		if (clicked)
		{
			isActive = false;
		}
	}

}

void EntryTextBox::setBarPos()
{
	float xval = textBox.getLastLetterPosition().x;
	textBar.setPosition(sf::Vector2f(xval, textBar.getPosition().y));
}

