#include "ResourceManager.hpp"


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************


ResourceManager::ResourceManager()											//Constructor
{
	setVectorSize(4);
	resourceManagerLogger = logger::getSLogger();
}





void ResourceManager::addFilesFromTree(const std::string& directory)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromTree(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Tree " << directory << " did not produce any files.";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			addFile(files[i], getFileName(files[i]));
		}
	}

}


void ResourceManager::addFilesFromTreeWithExt(const std::string& directory, const std::string& ext)
{
	bool extensionFound = false;
	std::vector<const std::string> files;
	fillFileNameVectorFromTree(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Tree " << directory << " did not produce any files.";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))						//treats "png" and ".png" as the extension the same
			{
				BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				addFile(files[i], getFileName(files[i]));
				extensionFound = true;
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory tree " << directory;
		}
	}
}




void ResourceManager::addFilesFromDirectory(const std::string& directory)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			addFile(files[i], getFileName(files[i]));
		}
	}

}


void ResourceManager::addFilesFromDirectoryWithExt(const std::string& directory, const std::string& ext)
{
	bool extensionFound = false;
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files.";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))						//treats "png" and ".png" as the extension the same
			{
				BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				addFile(files[i], getFileName(files[i]));
				extensionFound = true;
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory " << directory;
		}
	}
}

void ResourceManager::addFilesResourceGroupFromDirectory(const std::string& directory)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			addFile(files[i], getFileName(files[i]));
		}
	}


	std::string directoryName = getDirectoryName(directory);
	addEmptyResourceGroup(directoryName);
	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(directoryName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
	}

}


void ResourceManager::addFilesResourceGroupFromDirectory(const std::string& directory, const std::string& RGName)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);
	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			addFile(files[i], getFileName(files[i]));
		}
	}


	addEmptyResourceGroup(RGName);
	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(RGName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
	}

}



void ResourceManager::addFile(const std::string& fileName, const std::string& name)		//adds a generic file
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





sf::Texture* ResourceManager::getTexturePointerByName(const std::string& fname)					//returns a pointer to a Texture
{
	sf::Texture* returnMe;																//make a temporary pointer to a texture

	returnMe = &textureVector[ntoi(fname, Texture_Names)];							//set it to the texture with the desired name  

	return returnMe;																	//return it
}


sf::Font* ResourceManager::getFontPointerByName(const std::string& fname)						//returns a pointer to a Font
{

	sf::Font* returnMe;																	//make a temporary pointer to a font

	returnMe = &fontVector[ntoi(fname, Font_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it
	
}


sf::SoundBuffer* ResourceManager::getSoundBufPointerByName(const std::string& fname)			//returns a pointer to a soundbuf
{

	sf::SoundBuffer* returnMe;																	//make a temporary pointer to a font

	returnMe = &soundBufVector[ntoi(fname, SoundBuf_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it

}





void ResourceManager::addEmptyResourceGroup(const std::string& fname)								//adds an empty resourceGroup and give it a name
{
	ResourceGroup empt;																		//make an empty resource group

	resourceGroups.push_back(empt);															//add it
	
	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);							//add the name
}


void ResourceManager::addResourceGroup(ResourceGroup fResourceGroup, const std::string& fname)		//adds an already created resourceGroup and name it
{

	resourceGroups.push_back(fResourceGroup);												//add the resourceGroup

	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);
	
}


void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, const std::string& ext)
{
	addResourcetoResourceGroup(rsName, fileName, ext, "NO_NAME");
}

void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, std::string ext, const std::string& desName)
{
	bool nodesname = (desName == "NO_NAME");

	if (ext[0] == '.')
	{
		ext.erase(0, 1);						//kills the dot if passed by accident
	}

	if (ext == "ttf")
	{
		if (nodesname)
		{
			addFonttoResourceGroup(rsName, fileName);
		}
		else
		{
			addFonttoResourceGroup(rsName, fileName, desName);
		}
	}



	else if (ext == "png" ||
		ext == "jpg" ||
		ext == "jpeg" ||
		ext == "bmp")
	{
		if (nodesname)
		{
			addTexturetoResourceGroup(rsName, fileName);
		}
		else
		{
			addTexturetoResourceGroup(rsName, fileName, desName);
		}
	}


	else if (ext == "wav" ||
		ext == "aif" ||
		ext == "mp3" ||
		ext == "mp2" ||
		ext == "ogg" ||
		ext == "raw")
	{
		if (nodesname)
		{
			addSoundBuftoResourceGroup(rsName, fileName);
		}
		else
		{
			addSoundBuftoResourceGroup(rsName, fileName, desName);
		}
	}
}


void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName)	//adds a Texture to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName));
																						//literally just add the texture
}

void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName), desName);
}



void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName)	//adds a Font to a ResourceGroup by name
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName));
																						//literally just add the font
}

void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName), desName);
	//literally just add the font
}


void ResourceManager::addSoundBuftoResourceGroup(const std::string& rsName, const std::string& sbName)	//adds a SoundBuf to a ResourceGroup by name
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuf(getSoundBufPointerByName(sbName));
}

void ResourceManager::addSoundBuftoResourceGroup(const std::string& rsName, const std::string& sbName, const std::string& desName)	//adds a SoundBuf to a ResourceGroup by name
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuf(getSoundBufPointerByName(sbName), desName);
}



ResourceGroup* ResourceManager::getResourceGroupByName(const std::string& fname)				//retrives a resourceGroup by name
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
	for (unsigned int i = 0; i < halfLength; i++)
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



std::string ResourceManager::getDirectoryName(const std::string& fpath)
{
	std::string revName = "";

	for (int i = fpath.size() - 1; ((i >= 0) && (fpath[i] != '\\')); i--)	//reads the path from the back, stops if it hits the beginning or a "\"
	{
		revName += fpath[i];												//records the name, letter by letter in reverse.
	}

	return reverseString(revName);
}




void ResourceManager::fillFileNameVectorFromTree(const std::string& directory, std::vector<const std::string>& namevec)
{

	boost::filesystem::path dir(directory);												//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))			//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);								//go through the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))
			{
				namevec.push_back(directory + "\\" + it->path().filename().string());						//if a file is a regular file, add it to files
			}
			else if (boost::filesystem::is_directory(it->status()))
			{
				fillFileNameVectorFromTree(directory + "\\" + it->path().filename().string(), namevec);		//if a "file" is actually a folder, recurse
				//using that folder as the directory
			}

		}

	}
	else
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistant.";
	}
}

//--

void ResourceManager::fillFileNameVectorFromDirectory(const std::string& directory, std::vector<const std::string>& namevec)
{

	boost::filesystem::path dir(directory);											//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))		//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);							//go throught the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))
			{
				namevec.push_back(directory + "\\" + it->path().filename().string());					//if a file is a regular file, add it to files
			}

		}

	}
	else
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistent.";
	}

}






void ResourceManager::addTexture(const std::string& fileName)									//private function; adds a Texture to the TextureVector
{
	sf::Texture texture;																//make a temporary texture

	if (!texture.loadFromFile(fileName))												//try to make it load from the file
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (Texture) failed to load.";				
																						// if it doesn't, there is an error
	}

	textureVector.push_back(texture);													//add the texture

}


void ResourceManager::addFont(const std::string& fileName)										//private function; adds a font to the FontVector
{
	sf::Font font;																		//make a temporary font

	if (!font.loadFromFile(fileName))													//try to make it load from the file
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (Font) failed to load.";			
																						// if it doesn't, there is an error
	}

	fontVector.push_back(font);															//add the font
}


void ResourceManager::addSoundBuf(const std::string& fileName)								//private function; adds a soundBuf to the soundBufVector
{

	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(fileName))
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (SoundBuffer) failed to load.";
	}
	soundBufVector.push_back(buffer);

}


