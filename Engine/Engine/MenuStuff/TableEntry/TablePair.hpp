#pragma once
#include "EntryTextBox.hpp"
class TablePair : public MenuElement
{
public:
	TablePair();
	TablePair( 	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor, sf::Texture* const bgTex,
				const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent, const double& spac
				);

	~TablePair();
	
	void setup( sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor, sf::Texture* const bgTex,
				const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent, const double& spac
				);

	void setKeyString(const std::string& kstr);
	void setEntryString(std::string& estr);

	//std::string getInput();

	void update() {};
	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);
	void draw(sf::RenderWindow& window, sf::Vector2f drawPos);
	void resetMD() {};


private:

	SingleTextBox keyText;
	SingleTextBox colonDivider;
	EntryTextBox entryBox;
	double spacing;

};

