#include "KeyboardData.hpp"


KeyboardData::KeyboardData()
{
}


KeyboardData::~KeyboardData()
{
}


void KeyboardData::keyPressed(const unsigned int keyVal)
{
	keysHit.push_back(keyVal);
}


void KeyboardData::keyReleased(const unsigned int keyVal)
{
	keysHit.erase(remove(keysHit.begin(), keysHit.end(), keyVal), keysHit.end());
	keysHeld.erase(remove(keysHit.begin(), keysHit.end(), keyVal), keysHit.end());
	keysReleased.push_back(keyVal);
}



bool KeyboardData::isKeyHit(const int& keyVal)
{
	bool hit = false;
	if (std::find(keysHit.begin(), keysHit.end(), keyVal) != keysHit.end())
	{
		hit = true;
	}
	return hit;
}


bool KeyboardData::isKeyHeld(const int& keyVal)
{
	bool hit = false;
	if (std::find(keysHeld.begin(), keysHeld.end(), keyVal) != keysHeld.end())
	{
		hit = true;
	}
	else if (std::find(keysHit.begin(), keysHit.end(), keyVal) != keysHit.end())
	{
		hit = true;
	}
	return hit;
}

bool KeyboardData::isKeyReleased(const int& keyVal)
{
	bool hit = false;
	if (std::find(keysReleased.begin(), keysReleased.end(), keyVal) != keysReleased.end())
	{
		hit = true;
	}
	return hit;
}


void KeyboardData::newFrameUpdate()
{
	for (unsigned int i = 0; i < keysHit.size(); i++)
	{
		keysHit.erase(remove(keysHit.begin(), keysHit.end(), i), keysHit.end());
		keysHeld.push_back(i);
	}

	for (unsigned int i = 0; i < keysReleased.size(); i++)
	{
		keysReleased.erase(remove(keysHit.begin(), keysHit.end(), i), keysHit.end());
	}

}