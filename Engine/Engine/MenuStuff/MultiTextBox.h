#pragma once
#include "SingleTextBox.h"


class MultiTextBox : public MenuElement, public NameSearchable				//a named collection of textboxes -- useful for changing text
{
public:

	MultiTextBox();															//constructor

	~MultiTextBox();														//destructor
		

	//inherited virtual
	void update();

	void update(MouseData& fmouseData, const char& typedChar, KeyboardData& fkeyData);

	void draw(sf::RenderWindow& frenderwindow, sf::Vector2f drawPosition);

	void resetMD();



	void setCurrentTextBoxByName(std::string fname);						//set the textbox being drawn by name -- can only draw one at a time

	void setCurrentTextBoxByIndex(int findex);								//set the textbox being drawn by index 

	void addTextBox(SingleTextBox fsingleTextBox, std::string fname);		//adds a textbox and name to the collection

	void addTextBox(SingleTextBox fsingleTextBox, int finame);				//adds a textbox and inted name to the collection
	
	SingleTextBox* getTextBoxPointerByName(std::string fname);				//returns a pointer to a textbox by name

	SingleTextBox* getTextBoxPointerByIndex(int findex);					//returns a pointer to a textbox by index



private:

	
	std::vector<SingleTextBox> textBoxVector;								//the collection of textboxes

	int CTBIndex;															//current textbox index


};

