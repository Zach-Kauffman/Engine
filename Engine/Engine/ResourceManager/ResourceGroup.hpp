#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Namesearchable/NameSearchable.hpp"

class ResourceGroup : public NameSearchable								//essentially just a group of Textures, Fonts, and soundBuffers
{

public:

	ResourceGroup();													//Constructor -- empty
	~ResourceGroup();

	void addTexture(sf::Texture * const & ftexture);								//adds a texture

	void addTexture(sf::Texture * const & ftexture, const std::string& name);			//adds a texture


	void addFont(sf::Font* const & ffont);										//adds a font

	void addFont(sf::Font* const & ffont, const std::string& name);					//adds a font


	void addSoundBuffer(sf::SoundBuffer * const & fsoundbuf);						//adds a soundBuf

	void addSoundBuffer(sf::SoundBuffer * const & fsoundbuf, const std::string& name);		//adds a soundBuf




	std::vector<const sf::Texture*> getTextureVector();						//returns the entire textureVector

	std::vector<const sf::Font*> getFontVector();								//returns the entire fontVector

	std::vector<const sf::SoundBuffer*> getSoundBufferVector();					//returns the entire SoundBufVector


	const sf::Texture* getTexturePointer(const int& index);							//returns an element of textureVector

	const sf::Texture* getTexturePointer(const std::string& name);					//returns an element of textureVector


	const sf::Font* getFontPointer(const int& index);								//returns an element of fontVector

	const sf::Font* getFontPointer(const std::string& name);							//returns an element of fontVector


	const sf::SoundBuffer* getSoundBufferPointer(const int& findex);					//returns an element of soundBufVector

	const sf::SoundBuffer* getSoundBufferPointer(const std::string& findex);					//returns an element of soundBufVector



private:

	std::vector<const sf::Texture*> textureVector;							//vector of Textures

	std::vector<const sf::Font*> fontVector;									//vector of Fonts

	std::vector<const sf::SoundBuffer*> soundBufferVector;						//vector of SoundBuffers


	const enum VectorNames { Texture_Vector = 0, Font_Vector = 1, SoundBuffer_Vector = 2 };
};

