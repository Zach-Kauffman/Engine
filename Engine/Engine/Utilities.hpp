#pragma once


#include <string>
#include <stack>
#include <vector>


namespace util
{
	void swapChars(char& a, char& b);	//flips two chars

	std::string reverseString(const std::string& str);	//stack based implementation of string inversion

	std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split);	//splits string into parts seperated by "split"


	int imax(int& a, int& b);								//finds the greater of two ints
	int imin(int& a, int& b);								//finds the lesser of two ints
	void ibound(int& a, const int& b, const int& c);		//bounds an int between two other ints

	double dmax(double& a, double& b);						//finds the greater of two doubles
	double dmin(double& a, double& b);						//finds the lesser of two doubles
	void dbound(double& a, const double& b, const double& c);
															//bounds an double between two other doubles


	unsigned int uimax(unsigned int& a, unsigned int& b);	//finds the greater of two unsigned ints
	unsigned int uimin(unsigned int& a, unsigned int& b);	//finds the greater of two nsigned ints
	void uibound(unsigned int& a, const unsigned int& b, const unsigned int& c);
															//bounds an unsigned int between two other unsigned ints

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




