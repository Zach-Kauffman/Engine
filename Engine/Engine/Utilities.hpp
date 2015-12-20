#pragma once


#include <string>
#include <stack>
#include <vector>


namespace util
{
	void swapChars(char& a, char& b);	//flips two chars

	std::string reverseString(const std::string& str);	//stack based implementation of string inversion

	std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split);	//splits string into parts seperated by "split"
}




