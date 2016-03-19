#pragma once
#include <SFML/Graphics.hpp>
#include "..\Utility\Utilities.hpp"
class EntryTextBox
{
public:
	EntryTextBox();
	EntryTextBox(const sf::Font& textFont, const sf::Texture& barTex, const f::Texture& bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz);
	~EntryTextBox();

	void setup(const sf::Font& textFont, const sf::Texture barTex, sf::Texture bgTex, sf::Vector2f fpos,  const unsigned int& charsiz);


	void update();
	void 
private:

	sf::Vector2f position;
	sf::Text entryText;
	std::string entryString;
	sf::Sprite textBar;
	sf::Sprite background;
};

