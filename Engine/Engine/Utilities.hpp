#pragma once


#include <string>
#include <stack>
#include <vector>


namespace util
{
	void swapChars(char& a, char& b);	//flips two chars

	std::string reverseString(const std::string& str);	//stack based implementation of string inversion

	std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split);	//splits string into parts seperated by "split"

	template<class T>
	void nullCopyVector(const std::vector<T>& toCopy, std::vector<T>& vec)	//only copies non-null values from vector
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (toCopy[i])
			{
				vec[i] = toCopy[i];
			};
		}
	}

	template<class T>
	void nullCopyValue(const T& toCopy, T& value)	//only copies a non-null value
	{
		if (toCopy)
		{
			value = toCopy;
		}
	}
}




