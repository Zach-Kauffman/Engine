#include "ResourceGroup.hpp"

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************


ResourceGroup::ResourceGroup()	
{
	setVectorSize(3);		//set name map number to 3; texture, fint, soundbuffer
}

ResourceGroup::~ResourceGroup()
{

}


void ResourceGroup::addTexture(sf::Texture * const & ftexture)
{

	textureVector.push_back(ftexture);												//add texture

	addName(textureVector.size() - 1, Texture_Vector, textureVector.size() - 1);	//add "int name"

}

void ResourceGroup::addTexture(sf::Texture * const & ftexture, const std::string& fname)
{

	textureVector.push_back(ftexture);												//add texture
	addName(fname, Texture_Vector, textureVector.size() - 1);						//add name

}

void ResourceGroup::addFont(sf::Font * const & ffont)	
{

	fontVector.push_back(ffont);
	addName(fontVector.size() - 1, Font_Vector, fontVector.size() - 1);

}

void ResourceGroup::addFont(sf::Font * const & ffont, const std::string& fname)
{

	fontVector.push_back(ffont);
	addName(fname, Font_Vector, fontVector.size() - 1);


}

void ResourceGroup::addSoundBuffer(sf::SoundBuffer * const & fsoundbuf)
{

	soundBufferVector.push_back(fsoundbuf);
	addName(soundBufferVector.size() - 1, SoundBuffer_Vector, soundBufferVector.size() - 1);


}

void ResourceGroup::addSoundBuffer(sf::SoundBuffer * const & fsoundbuf, const std::string& fname)
{

	soundBufferVector.push_back(fsoundbuf);
	addName(fname, SoundBuffer_Vector, soundBufferVector.size() - 1);


}

void ResourceGroup::addShader(sf::Shader * const & fshader)
{
	shaderVector.push_back(fshader);
	addName(shaderVector.size() - 1, Shader_Vector, shaderVector.size() - 1);
}

void ResourceGroup::addShader(sf::Shader * const & fshader, const std::string& fname)
{
	shaderVector.push_back(fshader);
	addName(fname, Shader_Vector, shaderVector.size() - 1);
}




const sf::Texture* ResourceGroup::getTexturePointer(const int& index)
{

	return textureVector[index];						//returns the const texture pointer at spot index

}

const sf::Texture* ResourceGroup::getTexturePointer(const std::string& name)
{

	return textureVector[ntoi(name, Texture_Vector)];	//returns the const texture pointer by name

}

const sf::Font* ResourceGroup::getFontPointer(const int& index)
{

	return fontVector[index];

}

const sf::Font* ResourceGroup::getFontPointer(const std::string& name)
{

	return fontVector[ntoi(name, Texture_Vector)];

}

const sf::SoundBuffer* ResourceGroup::getSoundBufferPointer(const int& index)
{

	return soundBufferVector[index];

}

const sf::SoundBuffer* ResourceGroup::getSoundBufferPointer(const std::string& name)							//returns an element of soundbufvector -- a pointer to a soundbuffer
{

	return soundBufferVector[ntoi(name, SoundBuffer_Vector)];

}

const sf::Shader* ResourceGroup::getShaderPointer(const int& index)
{

	return shaderVector[index];

}

const sf::Shader* ResourceGroup::getShaderPointer(const std::string& name)
{

	return shaderVector[ntoi(name, Shader_Vector)];

}


