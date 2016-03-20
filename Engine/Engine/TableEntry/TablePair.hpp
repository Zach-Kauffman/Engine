#pragma once
#include "EntryTextBox.hpp"
class TablePair
{
public:
	TablePair();
	TablePair( sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz, const double& spac);
	~TablePair();
	
	void setup( sf::Font * const  font, sf::Texture * const barTex, sf::Texture * const bgTex, const sf::Vector2f& fpos, const unsigned int& charsiz, const double& spac);

	void setKeyString(const std::string& kstr);

	std::string getInput();

	void update(const std::string& curstr, MouseData& mdata);
	void draw(const sf::Vector2f& drawpos, sf::RenderWindow& window);


private:

	sf::Vector2f position;
	sf::Text keyString;
	sf::Text colonDivider;
	EntryTextBox entryBox;
	double spacing;

};

