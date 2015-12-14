#include "ResourceManager.hpp"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************


ResourceManager::ResourceManager()											//Constructor
{
	setVectorSize(4);
	resourceManagerLogger = logger::getSLogger();
}



//----------------------------------------------------------------------------------------------------------------------------***************************


void ResourceManager::addFilesFromTree(const std::string& directory)
{

	std::vector<std::string> files;														//the files to be added
	boost::filesystem::path dir(directory);												//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))			//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);								//go through the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))					
			{
				files.push_back(it->path().filename().string());						//if a file is a regular file, add it to files
			}
			else if (boost::filesystem::is_directory(it->status()))
			{
				addFilesFromTree(directory + "\\" + it->path().filename().string());	//if a "file" is actually a folder, recurse
																						//using that folder as the directory
			}

		}

		for (int i = 0; i < files.size(); i++)
		{

			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File:" << files[i];	

			addFile(directory + "\\" + files[i], getFileName(files[i]));				//go through files, adding them

		}

	}
	else
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistant.";
	}
}


void ResourceManager::addFilesFromDirectory(const std::string& directory)
{
	
	std::vector<std::string> files;													//the files to be added
	boost::filesystem::path dir(directory);											//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))		//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);							//go throught the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))					
			{
				files.push_back(it->path().filename().string());					//if a file is a regular file, add it to files
			}

		}

		for (int i = 0; i < files.size(); i++)
		{

			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File:" << files[i];	

			addFile(directory + "\\" + files[i], getFileName(files[i]));			//go through files, adding them

		}

	}
	else
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistant.";
	}


}


/*------------------------------------------------------------------------------------
-------------------------------addFile------------------------------------------------
------------------------------------------------------------------------------------*/

void ResourceManager::addFile(std::string fileName, std::string name)		//adds a generic file
{
	std::string ext = getExtension(fileName);								//get the extension

	if (ext == "ttf")														//.ttf is a font
	{
		addFont(fileName);													//add the font

		addName(name, Font_Names, fontVector.size() - 1);				//add the name
	}



	else if (	ext == "png" || 
				ext == "jpg" || 
				ext == "jpeg" ||	
				ext == "bmp")												//these extensions are textures
	{
		addTexture(fileName);												//add the texture

		addName(name, Texture_Names, textureVector.size() - 1);				//add the name
	}


	else if (	ext == "wav" ||
				ext == "aif" ||
				ext == "mp3" ||
				ext == "mp2" ||
				ext == "ogg" ||
				ext == "raw")
	{
		addSoundBuf(fileName);
		addName(name, SoundBuf_Names);
	}

	std::cout << fileName << ", " << name << std::endl;
}


sf::Texture* ResourceManager::getTexturePointerByName(std::string fname)					//returns a pointer to a Texture
{
	sf::Texture* returnMe;																//make a temporary pointer to a texture

	returnMe = &textureVector[ntoi(fname, Texture_Names)];							//set it to the texture with the desired name  

	return returnMe;																	//return it
}


sf::Font* ResourceManager::getFontPointerByName(std::string fname)						//returns a pointer to a Font
{

	sf::Font* returnMe;																	//make a temporary pointer to a font

	returnMe = &fontVector[ntoi(fname, Font_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it
	
}


sf::SoundBuffer* ResourceManager::getSoundBufPointerByName(std::string fname)			//returns a pointer to a soundbuf
{

	sf::SoundBuffer* returnMe;																	//make a temporary pointer to a font

	returnMe = &soundBufVector[ntoi(fname, SoundBuf_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it

}


void ResourceManager::addEmptyResourceGroup(std::string fname)								//adds an empty resourceGroup and give it a name
{
	ResourceGroup empt;																		//make an empty resource group

	resourceGroups.push_back(empt);															//add it
	
	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);							//add the name
}


void ResourceManager::addResourceGroup(ResourceGroup fResourceGroup, std::string fname)		//adds an already created resourceGroup and name it
{

	resourceGroups.push_back(fResourceGroup);												//add the resourceGroup

	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);
	
}


void ResourceManager::addTexturetoResourceGroup(std::string rsName, std::string texName)	//adds a Texture to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName));
																						//literally just add the texture
}


void ResourceManager::addFonttoResourceGroup(std::string rsName, std::string fontName)	//adds a Font to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName));
																						//literally just add the font
	
}


void ResourceManager::addSoundBuftoResourceGroup(std::string rsName, std::string sbName)	//adds a SoundBuf to a ResourceGroup by name
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuf(getSoundBufPointerByName(sbName));
}


ResourceGroup* ResourceManager::getResourceGroupByName(std::string fname)				//retrives a resourceGroup by name
{

	return &resourceGroups[ntoi(fname, ResourceGroup_Names)];							//returns the resource set with the desired name
	
}






//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PRIVATE----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



void ResourceManager::swapChars(char& a, char& b)			//swaps the values of two chars
{
	char c = a;
	a = b;
	b = c;
}

std::string ResourceManager::reverseString(std::string str)	//reverses a string
{
	unsigned int halfLength = str.size() / 2;
	unsigned int siz = str.size() - 1;
	for (int i = 0; i < halfLength; i++)
	{
		swapChars(str[i], str[siz - i]);					//essentially just swaps each pair of chars that are equidistant from the center
	}

	return str;
}


std::string ResourceManager::getExtension(const std::string& fpath)			//returns the extension of a file
{
	std::string reverseExt = "";											//will be a reversed file extension

	for (int i = fpath.size() - 1; ((i >= 0) && (fpath[i] != '.')); i--)	/*cycles from the back of the file name and records the reversed 
																			file extension (goes to the '.' or the beginning)*/
	{
		reverseExt += fpath[i];												//record the letter -- will be backwards when done in succession
	}

	return reverseString(reverseExt);										//simply reverse the string and return it
}


std::string ResourceManager::getFileName(const std::string& fpath)
{
	std::string revName = "";												//the reversed file name
	bool record = false;													//whether to record the char or not

	for (int i = fpath.size() - 1; ((i >= 0) && (fpath[i] != '\\')); i--)	//reads the path from the back, stops if it hits the beginning or a [\]
	{
		if (!record && fpath[i] == '.')										
		{
			record = true;													//once it's past the extension, it starts recording
		}
		else if (record)
		{
			revName += fpath[i];											//records the name, letter by letter in reverse.
		}
	}

	return reverseString(revName);											//reverse the string and return it
}



void ResourceManager::addTexture(std::string fileName)									//private function; adds a Texture to the TextureVector
{
	sf::Texture texture;																//make a temporary texture

	if (!texture.loadFromFile(fileName))												//try to make it load from the file
	{
		std::cout << fileName << " (Texture) failed to load." << std::endl;				// if it doesn't, there is an error
	}

	textureVector.push_back(texture);													//add the texture

}


void ResourceManager::addFont(std::string fileName)										//private function; adds a font to the FontVector
{
	sf::Font font;																		//make a temporary font

	if (!font.loadFromFile(fileName))													//try to make it load from the file
	{
		std::cout << fileName << " (Font) failed to load." << std::endl;				// if it doesn't, there is an error
	}

	fontVector.push_back(font);															//add the font
}


void ResourceManager::addSoundBuf(std::string fileName)								//private function; adds a soundBuf to the soundBufVector
{

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(fileName))
	{
		std::cout << fileName << " (SoundBuffer) failed to load." << std::endl;
	}
	soundBufVector.push_back(buffer);

}


