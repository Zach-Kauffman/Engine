#include "ResourceGroup.h"

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************




ResourceGroup::ResourceGroup()												//Constructor is empty	
{
	setVectorSize(3);
}



//----------------------------------------------------------------------------------------------------------------------------***************************



void ResourceGroup::addTexture(sf::Texture* ftexture)						//add a pointer to a texture to textureVector
{

	textureVector.push_back(ftexture);
	addName(textureVector.size() - 1, Texture_Vector, textureVector.size() - 1);

}



void ResourceGroup::addTexture(sf::Texture* ftexture, std::string fname)						//add a pointer to a texture to textureVector
{

	textureVector.push_back(ftexture);
	addName(fname, Texture_Vector, textureVector.size() - 1);

}

//----------------------------------------------------------------------------------------------------------------------------***************************



void ResourceGroup::addFont(sf::Font* ffont)								//add a pointer to a font to fontVector
{

	fontVector.push_back(ffont);
	addName(fontVector.size() - 1, Font_Vector, fontVector.size() - 1);

}



void ResourceGroup::addFont(sf::Font* ffont, std::string fname)								//add a pointer to a font to fontVector
{

	fontVector.push_back(ffont);
	addName(fname, Font_Vector, fontVector.size() - 1);


}



//----------------------------------------------------------------------------------------------------------------------------***************************



void ResourceGroup::addSoundBuf(sf::SoundBuffer* fsoundbuf)						//add a pointer to a soundBuf to soundBufVector
{

	soundBufVector.push_back(fsoundbuf);
	addName(soundBufVector.size() - 1, SoundBuf_Vector, soundBufVector.size() - 1);


}



void ResourceGroup::addSoundBuf(sf::SoundBuffer* fsoundbuf, std::string fname)						//add a pointer to a soundBuf to soundBufVector
{

	soundBufVector.push_back(fsoundbuf);
	addName(fname, SoundBuf_Vector, soundBufVector.size() - 1);


}

//----------------------------------------------------------------------------------------------------------------------------***************************



std::vector<sf::Texture*> ResourceGroup::getTextureVector()					//returns the entire textureVector; probably not going to use
{

	return textureVector;

}



//----------------------------------------------------------------------------------------------------------------------------***************************



std::vector<sf::Font*> ResourceGroup::getFontVector()						//returns the entire fontVector; probably not going to use
{

	return fontVector;

}



//----------------------------------------------------------------------------------------------------------------------------***************************



std::vector<sf::SoundBuffer*> ResourceGroup::getSoundBufVector()			//returns the entire soundBufVector; probably not going to use
{

	return soundBufVector;

}



//----------------------------------------------------------------------------------------------------------------------------***************************



sf::Texture* ResourceGroup::getTexturePointer(int findex)					//returns an element of textureVector -- a pointer to a texture
{

	return textureVector[findex];

}



sf::Texture* ResourceGroup::getTexturePointer(std::string fname)					//returns an element of textureVector -- a pointer to a texture
{

	return textureVector[ntoi(fname, Texture_Vector)];

}

//----------------------------------------------------------------------------------------------------------------------------***************************


sf::Font* ResourceGroup::getFontPointer(int findex)							//returns an element of fontVector -- a pointer to a font
{

	return fontVector[findex];

}


sf::Font* ResourceGroup::getFontPointer(std::string fname)							//returns an element of fontVector -- a pointer to a font
{

	return fontVector[ntoi(fname, Texture_Vector)];

}


//----------------------------------------------------------------------------------------------------------------------------***************************


sf::SoundBuffer* ResourceGroup::getSoundBufPointer(int findex)							//returns an element of soundbufvector -- a pointer to a soundbuffer
{

	return soundBufVector[findex];

}



sf::SoundBuffer* ResourceGroup::getSoundBufPointer(std::string fname)							//returns an element of soundbufvector -- a pointer to a soundbuffer
{

	return soundBufVector[ntoi(fname, SoundBuf_Vector)];

}
//----------------------------------------------------------------------------------------------------------------------------***************************