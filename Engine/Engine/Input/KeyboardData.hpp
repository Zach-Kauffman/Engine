#pragma once
#include <SFML/Graphics.hpp>

class KeyboardData
{
public:
	KeyboardData();
	~KeyboardData();

	void keyPressed(const unsigned int keyVal);
	void keyReleased(const unsigned int keyVal);


	bool isKeyHit(const int& keyVal);
	bool isKeyHeld(const int& keyVal);	
	bool isKeyReleased(const int& keyVal);
	//bool isKeyUnheld(const int& keyVal); //not useful

	void newFrameUpdate();						//call once every time frame repeats

private:

	std::vector<const int> keysHit;
	std::vector<const int> keysHeld;
	std::vector<const int> keysReleased;
};

