#include "EntryTextBox.hpp"


EntryTextBox::EntryTextBox()
{
	//strTracker = "";
	//*entryString = "a";
	background.setPosition(0, 0);
	entryText.setPosition(10, 10);
	textBar.setPosition(0, 10);
	isActive = false;
}


EntryTextBox::~EntryTextBox()
{
}


EntryTextBox::EntryTextBox(sf::Font * const font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz)
{

	setup(font, barTex, bgTex, fpos, charsiz);

}

void EntryTextBox::setup(sf::Font * const font, sf::Texture * const barTex, sf::Texture * const bgTex, sf::Vector2f fpos,  const unsigned int& charsiz)
{
	background.setTexture(*bgTex);
	position = fpos;
	entryText.setFont(*font);
	entryText.setCharacterSize(charsiz);
	entryText.setColor(sf::Color::Red);
	textBar.setTexture(*barTex);
}


void EntryTextBox::setEntryString(std::string& estr)
{
	entryString = &estr;
}
//std::string EntryTextBox::getEntryString()
//{
//	return entryString;
//}


void EntryTextBox::update(const char& typedChar, MouseData& mdata)
{
	setActivity(mdata);
	setEntryString(typedChar);
	if (isActive)
	{
		entryText.setString(*entryString);
	}
	setBarPos();



}

void EntryTextBox::draw(const sf::Vector2f& drawPos, sf::RenderWindow& window)
{
	if (lastDrawPos != drawPos)
	{
		lastDrawPos = drawPos;
	}
	
	position += drawPos;

	background.move(position);
	window.draw(background);
	background.move(-position);


	entryText.move(position);
	window.draw(entryText);
	entryText.move(-position);

	if (isActive)
	{
		textBar.move(position);
		window.draw(textBar);
		textBar.move(-position);
	}

	



	position -= drawPos;
}

//private

void EntryTextBox::setEntryString(const char& typedChar)
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
	if (background.getGlobalBounds().contains(mpos))
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
	float xval = entryText.getGlobalBounds().width + entryText.getPosition().x;
	textBar.setPosition(sf::Vector2f(xval, textBar.getPosition().y));
}


//bool EntryTextBox::isDif(const std::string& curstr,  const unsigned int& i)
//{
//	bool b = false;
//	if (strTracker == "" && curstr != "")
//	{
//		b = true;
//	}
//	else if (strTracker.size() <= i)
//	{
//		b = true;
//	}
//	else if (curstr[i] != strTracker[i])
//	{
//		b = true;
//	}
//	return b;
//}