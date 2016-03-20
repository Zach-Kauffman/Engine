#pragma once
#include <SFML/Graphics.hpp>
#include "..\Utility\Utilities.hpp"
#include "..\Input\KeyboardData.hpp"
#include "..\Input\MouseData.hpp"
class EntryTextBox
{
public:
	EntryTextBox();
	EntryTextBox(sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz);
	~EntryTextBox();

	void setup(sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, sf::Vector2f fpos,  const unsigned int& charsiz);

	std::string getEntryString();

	void update(const std::string& curstr, MouseData& mdata);
	void draw(const sf::Vector2f& drawPos, sf::RenderWindow& window);
private:

	void setEntryString(const std::string& curstr);
	void setActivity(MouseData& mdata);
	void setBarPos();

	sf::Vector2f position;
	sf::Vector2f lastDrawPos;

	sf::Text entryText;
	std::string strTracker;
	std::string entryString;
	sf::Sprite textBar;
	sf::Sprite background;
	
	bool isActive;

};

