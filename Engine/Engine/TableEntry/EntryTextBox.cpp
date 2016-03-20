#include "EntryTextBox.hpp"


EntryTextBox::EntryTextBox()
{
	strTracker = "";
	background.setPosition(0, 0);
	entryText.setPosition(0, 0);
	textBar.setPosition(0, 0);
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
	entryText.setColor(sf::Color::Green);
	textBar.setTexture(*barTex);
}


std::string EntryTextBox::getEntryString()
{
	return entryString;
}


void EntryTextBox::update(const std::string& curstr, MouseData& mdata)
{
	setActivity(mdata);
	setEntryString(curstr);
	if (isActive)
	{
		entryText.setString(entryString);
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

void EntryTextBox::setEntryString(const std::string& curstr)
{
	

	if (!isActive)
	{
		strTracker = curstr;
	}
	else
	{
		bool dif = false;
		bool renewOnce = true;
		for (unsigned int i = 0; i < curstr.size(); i++)
		{
			if (curstr[i] != strTracker[i] && !dif)
			{
				dif = true;
			}
			if (dif)
			{
				if (renewOnce)
				{
					entryString = "";
					renewOnce = false;
				}
				entryString += curstr[i];
			}
		}
	}

}


void EntryTextBox::setActivity(MouseData& mdata)
{
	sf::Vector2f mpos = mdata.getPosition() - lastDrawPos + position;
	bool clicked = (mdata.getLeftData() == MouseData::Hit);
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
	float xval = entryText.findCharacterPos(entryString.size() - 1).x;
	textBar.setPosition(sf::Vector2f(xval, textBar.getPosition().y));
}