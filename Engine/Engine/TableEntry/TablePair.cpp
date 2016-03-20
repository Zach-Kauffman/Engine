#include "TablePair.hpp"


TablePair::TablePair()
{
}


TablePair::~TablePair()
{
}



TablePair::TablePair( sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz, const double& spac)
{
	setup(font, barTex, bgTex, fpos, charsiz, spac);
}

	
void TablePair::setup( sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz, const double& spac)
{
	position = fpos;

	keyString.setFont(*font);
	keyString.setCharacterSize(charsiz);
	keyString.setPosition(0, 0);
	keyString.setColor(sf::Color::Green);

	colonDivider.setFont(*font);
	colonDivider.setCharacterSize(charsiz);
	colonDivider.setString("|:|");
	colonDivider.setPosition(0, spac);
	colonDivider.setColor(sf::Color::Green);

	entryBox.setup(font, barTex, bgTex, sf::Vector2f(2*spac, 0), charsiz);

	
}

void TablePair::setKeyString(const std::string& kstr)
{
	keyString.setString(kstr);
}


std::string TablePair::getInput()
{
	return entryBox.getEntryString();
}


void TablePair::update(const std::string& curstr, MouseData& mdata)
{
	entryBox.update(curstr, mdata);
}

void TablePair::draw(const sf::Vector2f& drawpos, sf::RenderWindow& window)
{
	position += drawpos;

	keyString.move(drawpos);
	window.draw(keyString);
	keyString.move(-drawpos);

	colonDivider.move(drawpos);
	window.draw(colonDivider);
	colonDivider.move(-drawpos);


	entryBox.draw(position, window);


	position -= drawpos;
}