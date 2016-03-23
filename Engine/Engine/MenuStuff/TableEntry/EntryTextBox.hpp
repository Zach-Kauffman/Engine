#pragma once
#include <SFML/Graphics.hpp>
#include "..\..\Utility\Utilities.hpp"
#include "..\..\Input\KeyboardData.hpp"
#include "..\..\Input\MouseData.hpp"
#include <iostream>
#include "..\SingleTextBox.h"
#include "..\MenuSprite.h"
class EntryTextBox : public MenuElement
{
public:
	EntryTextBox();

	EntryTextBox(	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor,
					sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
				);

	~EntryTextBox();

	void setup(		sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor,
					sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
				);


	void setEntryString(std::string& estr);

	//std::string getEntryString();
	void update() {};
	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);
	void draw(sf::RenderWindow& window, sf::Vector2f drawPos);
	void resetMD() {};
private:

	void setEntryString(const char& typedChar);
	void setActivity(MouseData& mdata);
	void setBarPos();
	//bool isDif(const char& typedChar, const unsigned int& i);

	sf::Vector2f lastDrawPos;
	
	std::string* entryString;
	SingleTextBox textBox;
	MenuSprite textBar;
	MenuSprite background;
	
	bool isActive;

};

