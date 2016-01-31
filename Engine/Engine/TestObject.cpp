#include "TestObject.hpp"

using namespace objects;

TestObject::TestObject(){}

TestObject::~TestObject(){}

void TestObject::draw(Layer& renderTarget)
{
	renderTarget.draw(texCoords, testTex);
}

void TestObject::update()
{

}

void TestObject::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
{
	
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord

	//loading texture
	std::string textureName;
	parser.readValue<std::string>("texture", textureName, dataTree);
	testTex = resources.getTexturePointerByName(textureName);
	
	sf::Vector2f texSize = (sf::Vector2f)testTex->getSize();

	texCoords = sf::VertexArray(sf::Quads, 4); 

	//defining texture coordinates centered on position
	texCoords[0].position = sf::Vector2f(position.x + texSize.x / 2, position.y + texSize.y / 2);	//bottom right
	texCoords[1].position = sf::Vector2f(position.x - texSize.x / 2, position.y + texSize.y / 2);	//bottom left
	texCoords[2].position = sf::Vector2f(position.x + texSize.x / 2, position.y - texSize.y / 2);	//top right
	texCoords[3].position = sf::Vector2f(position.x - texSize.x / 2, position.y - texSize.y / 2);	//top left

	texCoords[0].texCoords = sf::Vector2f(texSize.x, texSize.y);			//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, texSize.y);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(texSize.x, 0);	//top right
	texCoords[3].texCoords = sf::Vector2f(0, 0);			//top left

}

void TestObject::write()
{
	//more INIParser stuff
}

