#pragma once
#include "ResourceGroup.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp" 



class ResourceManager : public NameSearchable								/*This class will basically hold all textures, fonts, and soundBufs.*/
{																			/*Part of this is unimpressive -- IT DOES NOT CURRENTLY
																			load all files from a directory.*/
	//typedef const std::string& crstring;

/*---------------------------------------------------------------------------------------------------------

NOTES: SoundBuffer doesnt work yet, so elements that pertain to them are likely commented out for now.

----------------------------------------------------------------------------------------------------------*/


public:

	ResourceManager();														//Constructor


	void addFilesFromTree(const std::string& directory);
	void addFilesFromTreeWithExt(const std::string& directory, const std::string& ext);

	void addFilesFromDirectory(const std::string& directory);
	void addFilesFromDirectoryWithExt(const std::string& directory, const std::string& ext);

	void addFilesResourceGroupFromDirectory(const std::string& directory);
	void addFilesResourceGroupFromDirectory(const std::string& directory, const std::string& RGName);

	void addFile(const std::string& fileName, const std::string& name);					//Adds a generic file



	sf::Texture* getTexturePointerByName(const std::string& name);					//retrieves a pointer to a texture
	sf::Font* getFontPointerByName( const std::string& name);						//Retrieves a pointer to a font
	sf::SoundBuffer* getSoundBufPointerByName(const std::string& name);



	void addEmptyResourceGroup(const std::string& name);								//sets a new empty resourceGroup to ResourceGroup
	void addResourceGroup(ResourceGroup fResourceGroup, const std::string& name);		//sets a currently filled resourceGroup to ResourceGroup

	void addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, const std::string& ext);
	void addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, std::string ext, const std::string& desName);

	void addTexturetoResourceGroup(const std::string& rsName, const std::string& texName);
	void addTexturetoResourceGroup(const std::string& rsName, const std::string& texName, const std::string& desName);

	void addFonttoResourceGroup(const std::string& rsName, const std::string& fontName);
	void addFonttoResourceGroup(const std::string& rsName, const std::string& fontName, const std::string& desName);	

	void addSoundBuftoResourceGroup(const std::string& rsName, const std::string& sbName);
	void addSoundBuftoResourceGroup(const std::string& rsName, const std::string& sbName, const std::string& desName);
	
	ResourceGroup* getResourceGroupByName(const std::string& fname);
	


private:

	void swapChars(char& a, char& b);
	std::string reverseString(std::string str);

	std::string getExtension(const std::string& fpath);
	std::string getFileName(const std::string& fpath);
	std::string getDirectoryName(const std::string& fpath);


	void fillFileNameVectorFromTree(const std::string& directory, std::vector<const std::string>& namevec);
	void fillFileNameVectorFromDirectory(const std::string& directory, std::vector<const std::string>& namevec);
	


	void addTexture(const std::string& fileName);									//adds a Texture
	void addFont(const std::string& fileName);										//adds a Font
	void addSoundBuf(const std::string& fileName);									//adds a SoundBuf




	std::vector<sf::Texture> textureVector;									//vector of Textures that will be used in the program

	std::vector<sf::Font> fontVector;										//vector of Fonts that will be used in the whole program
	
	std::vector<sf::SoundBuffer> soundBufVector;



	std::vector<ResourceGroup> resourceGroups;								/*presets for certain things like BasicButton. BasicButton will use
																			the preset Textures, Fonts, and SoundBuffers for BasicButton*/


	
	enum nameVectorIndeces {Texture_Names = 0, Font_Names = 1, SoundBuf_Names = 2, ResourceGroup_Names = 3}; 
																			//enum for accessing vectors more intuitively

	src::severity_logger<severity_level> resourceManagerLogger;
	
};

