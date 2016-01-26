#include "TestObject.hpp"

using namespace objects;

TestObject::TestObject(){}

TestObject::~TestObject(){}

void TestObject::draw(sf::RenderTexture& renderTarget)
{
	renderTarget.draw(texCoords, testTex);
}

void TestObject::update()
{

}

//void TestObject::load(boost::property_tree::ptree& propertyTree, ResourceManager& resources)
void TestObject::load(const std::string& tex, const int& x, const int &y, ResourceManager& resources)
{
	/*
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, propertyTree);
	parser.readValue<float>("position.<xmlattr>.y", position.y, propertyTree);

	std::string textureName;
	parser.readValue<std::string>("texture", textureName, propertyTree);
	*/
	position.x = x;
	position.y = y;
	testTex = resources.getTexturePointerByName(tex);
	
	sf::Vector2f texSize = (sf::Vector2f)testTex->getSize();

	texCoords = sf::VertexArray(sf::Quads, 4); 

	//defining texture coordinates centered on position
	texCoords[0].position = sf::Vector2f(position.x + texSize.x / 2, position.y + texSize.y / 2);	//bottom right
	texCoords[1].position = sf::Vector2f(position.x - texSize.x / 2, position.y + texSize.y / 2);	//bottom left
	texCoords[2].position = sf::Vector2f(position.x + texSize.x / 2, position.y - texSize.y / 2);	//top right
	texCoords[3].position = sf::Vector2f(position.x - texSize.x / 2, position.y - texSize.y / 2);	//top left

	texCoords[0].texCoords = sf::Vector2f(texSize.x, 0);			//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, 0);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(texSize.x, texSize.y);	//top right
	texCoords[3].texCoords = sf::Vector2f(0, texSize.y);			//top left

}

void TestObject::write()
{
	//more INIParser stuff
}

