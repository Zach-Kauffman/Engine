#include "NameSearchable.hpp"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************






NameSearchable::NameSearchable()
{

}






NameSearchable::~NameSearchable()
{

}


//----------------------------------------------------------------------------------------------------------------------------***************************





//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PROTECTED--------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************





std::string NameSearchable::intToString(int finput)		//converts an int to a string using boost
{
	return boost::lexical_cast<std::string>(finput);
}




//----------------------------------------------------------------------------------------------------------------------------***************************




int NameSearchable::ntoi(std::string fname)				//accesses the nameMap to get the int associated with the name (assumes the amount of name maps is 1)
{
	return ntoi(fname, 0);								//assumes the index is 0
}





int NameSearchable::ntoi(std::string fname, int findex)	//accesses the nameMap to get the int associated with the name
{
	return nameMapVector[findex][fname];				//returns the int associated with the name of the "findexth" vector (for instance, textures as oppesd to fonts)			

}




//----------------------------------------------------------------------------------------------------------------------------***************************




void NameSearchable::setVectorSize(int fsize)			//resizes the vector of name maps -- typically used only once
{
	nameMapVector.resize(fsize);						//resize it
}




//----------------------------------------------------------------------------------------------------------------------------***************************


//--1

void  NameSearchable::addName(int fintname, int fend)	//adds an int 'name' (used for general creation of things) and an index, assuming the vector index is 0 
{
	addName(fintname, 0, fend);							//assumes the vector index is 0
}




//--2

void  NameSearchable::addName(int fintname, int findex, int fend)		//adds an int 'name', a desired index, and a vector index
{
	std::string tmpString = "Unnamed" + intToString(fintname) + ".";	//make a name out of the int (23 -> "Unnamed23.") the '.' is to prevent multiple copies 
																		//from having confusing names (e.g. add 2 then 2 again, you get "Unnamed2." and "Unnamed2.2"
																		//rather than "Unnamed2" and "Unnamed22"

	addName(tmpString, findex, fend);									//then add the name using the string-ified int
}




//--3

void NameSearchable::addName(std::string fname, int fend)				//adds a name and a desired index to map to, assuming the vector index is 0 
{
	addName(fname, 0, fend);											//assume the vector index is 0
}




//--4
void NameSearchable::addName(std::string fname, int findex, int fend)	//the BIG one -- adds a name, an index to correspond to, and a vector index
{
	bool sameName = true;								//true if there may be a duplicate already
	bool firstDuplicate = true;							//true if the duplicate found was the first duplicate

	while (sameName == true)							//go through, finding duplicates
	{
		if (nameMapVector[findex].count(fname) == 1)
		{
			if (firstDuplicate == true)
			{
				fname += "2";							/*if there exists a "RedTexture" already, and you try to add another one,
														it will become "RedTexture2"		*/
				firstDuplicate = false;
			}
			else
			{
				fname[fname.size() - 1]++;				/*if there exists a "RedTexture" and a "RedTexture2" already, and you try to add another "RedTexture",
														it will become "RedTexture3"		*/
			}

		}
		else
		{
			sameName = false;							//if there is no same name, exit the while loop
		}
	}

	nameMapVector[findex][fname] = fend;				//then add the altered (or not) name
}
