#include "ResourceManager.hpp"

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************


ResourceManager::ResourceManager()						//Constructor
{
	setVectorSize(4);									//set the vector of name maps to 4: Textures, Fonts, SoundBuffers, ResourceGroups

	resourceManagerLogger = logger::getSLogger();		//setup the logger
}

ResourceManager::~ResourceManager()						//destructor
{

}



void ResourceManager::addFilesFromTree(const std::string& directory)
{
	std::vector<const std::string> files;			//make a vector of files
	fillFileNameVectorFromTree(directory, files);	//fill it

	if (!files.size())
	{
		BOOST_LOG(resourceManagerLogger, WARNING) << "Tree " << directory << " did not produce any files";
													//Log a warning if files is empty
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			addFile(files[i], getFileName(files[i]));
													//otherwise, add the file and give a debug message
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
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))		
													//treats "png" and ".png" as the extension the same
			{
				BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				addFile(files[i], getFileName(files[i]));
				extensionFound = true;
													//if the extension matched, add the file
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory tree " << directory;
													//if no files with that extension were found in the tree, logs a warning message
		}
	}
}

void ResourceManager::addFilesFromDirectory(const std::string& directory)
{
	std::vector<const std::string> files;				//make a vector of filenames
	fillFileNameVectorFromDirectory(directory, files);	//fill it

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
														//add the files
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
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))
														//treats "png" and ".png" the same
			{
				BOOST_LOG(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				addFile(files[i], getFileName(files[i]));
				extensionFound = true;
														//if the extension matches, add the file
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory " << directory;
														//give a warning if no files with that extension was found in the directory
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
	addEmptyResourceGroup(directoryName);				//make an empty resourceGroup with the name of the directory

	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(directoryName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
														//add the files to the resourceGroup
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


	addEmptyResourceGroup(RGName);						//make a new empty resourceGroup with the specified name

	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(RGName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
														//add the files	
	}

}



void ResourceManager::addFile(const std::string& fileName, const std::string& name)
{
	std::string ext = getExtension(fileName);						//get the extension

	if (ext == "ttf")												//.ttf is a font
	{
		addFont(fileName);											//add the font

		addName(name, Font_Names, fontVector.size() - 1);			//add the name
	}
	else if (	ext == "png" || 
				ext == "jpg" || 
				ext == "jpeg" ||	
				ext == "bmp")										//these extensions are textures
	{
		addTexture(fileName);										//add the texture

		addName(name, Texture_Names, textureVector.size() - 1);		//add the name
	}
	else if (	ext == "wav" ||
				ext == "aif" ||
				ext == "mp3" ||
				ext == "mp2" ||
				ext == "ogg" ||
				ext == "raw")										//these are soundBuffers
	{
		addSoundBuffer(fileName);

		addName(name, SoundBuffer_Names);
	}

	nameMapVector[Texture_Names];
}



sf::Texture* ResourceManager::getTexturePointerByName(const std::string& name)	
{

	return &textureVector[ntoi(name, Texture_Names)];				//return the texture with the desired name  

}

sf::Font* ResourceManager::getFontPointerByName(const std::string& name)
{

	return &fontVector[ntoi(name, Font_Names)];					//return the desired font

}

sf::SoundBuffer* ResourceManager::getSoundBufferPointerByName(const std::string& name)
{

	return &soundBufferVector[ntoi(name, SoundBuffer_Names)];		//set it to the font with the desired name

}



void ResourceManager::addEmptyResourceGroup(const std::string& name)		//adds an empty resourceGroup and give it a name
{
	ResourceGroup empt;														//make an empty resource group

	resourceGroups.push_back(empt);											//add it
	
	addName(name, ResourceGroup_Names, resourceGroups.size() - 1);			//add the name
}

void ResourceManager::addResourceGroup(ResourceGroup fResourceGroup, const std::string& name)		
																			//adds an already created resourceGroup and name it
{

	resourceGroups.push_back(fResourceGroup);								//add the resourceGroup

	addName(name, ResourceGroup_Names, resourceGroups.size() - 1);			//add the name
	
}



void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, const std::string& ext)
{
	addResourcetoResourceGroup(rsName, fileName, ext, "NO_NAME");			//adds the resource without any name
}

void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, std::string ext, const std::string& desName)
{
	bool nodesname = (desName == "NO_NAME");	//if the name was "NO_NAME" we dont add the name

	if (ext[0] == '.')
	{
		ext.erase(0, 1);						//kills the dot if passed by accident
	}
												
	
	if (ext == "ttf")							//interprets the extension...
	{
		if (nodesname)
		{
			addFonttoResourceGroup(rsName, fileName);
												//if there was no name, add it without a name
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
			addSoundBuffertoResourceGroup(rsName, fileName);
		}
		else
		{
			addSoundBuffertoResourceGroup(rsName, fileName, desName);
		}
	}
}

void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName)	//adds a Texture to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName));
																										//literally just add the texture without a name
}

void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName), desName);
																										//add the texture with the name
}

void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName));
}

void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName), desName);
}

void ResourceManager::addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuffer(getSoundBufferPointerByName(sbName));
}

void ResourceManager::addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuffer(getSoundBufferPointerByName(sbName), desName);
}



ResourceGroup* ResourceManager::getResourceGroupByName(const std::string& name)
{

	return &resourceGroups[ntoi(name, ResourceGroup_Names)];	//returns the resource set with the desired name
	
}

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PRIVATE----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************

void ResourceManager::swapChars(char& a, char& b)				//swaps the values of two chars
{
	char c = a;
	a = b;
	b = c;
}

std::string ResourceManager::reverseString(std::string str)		//reverses a string
{
	unsigned int halfLength = str.size() / 2;
	unsigned int siz = str.size() - 1;
	for (unsigned int i = 0; i < halfLength; i++)
	{
		swapChars(str[i], str[siz - i]);						//essentially just swaps each pair of chars that are equidistant from the center
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

std::string ResourceManager::getDirectoryName(const std::string& fpath)		//kind of same as getFileName -- just assumes no extension
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
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistant";
	}
}

void ResourceManager::fillFileNameVectorFromDirectory(const std::string& directory, std::vector<const std::string>& namevec)
{

	boost::filesystem::path dir(directory);												//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))			//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);								//go throught the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))
			{
				namevec.push_back(directory + "\\" + it->path().filename().string());	//if a file is a regular file, add it to files
			}

		}

	}
	else
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistent";
	}

}



void ResourceManager::addTexture(const std::string& fileName)
{
	sf::Texture texture;										//make a temporary texture

	if (!texture.loadFromFile(fileName))						//try to make it load from the file
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (Texture) failed to load.";				
																// if it doesn't, there is an error
	}

	textureVector.push_back(texture);							//add the texture

}

void ResourceManager::addFont(const std::string& fileName)
{
	sf::Font font;

	if (!font.loadFromFile(fileName))
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (Font) failed to load.";			

	}

	fontVector.push_back(font);
}

void ResourceManager::addSoundBuffer(const std::string& fileName)
{

	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(fileName))
	{
		BOOST_LOG(resourceManagerLogger, ERROR) << fileName << " (SoundBuffer) failed to load.";
	}
	soundBufferVector.push_back(buffer);

}