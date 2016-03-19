#include "EntryTextBox.hpp"


EntryTextBox::EntryTextBox()
{
}


EntryTextBox::~EntryTextBox()
{
}


EntryTextBox::EntryTextBox(const sf::Font& textFont, const sf::Texture& barTex, const sf::Texture& bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz)
{

	setup(textFont, barTex, bgTex, fpos, charsiz);

}

void EntryTextBox::setup(const sf::Font& textFont, const sf::Texture barTex, sf::Texture bgTex, sf::Vector2f fpos,  const unsigned int& charsiz)
{
	background.setTexture(bgTex);
	position = fpos;
	entryText.setFont(textFont);
	entryText.setCharacterSize(charsiz);
	entryText.setColor(sf::Color::Green);
	textBar.setTexture(barTex);
}