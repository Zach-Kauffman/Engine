#include "MovingTestObject.hpp"

using namespace objects;

MovingTestObject::MovingTestObject(){}

MovingTestObject::~MovingTestObject(){}

void MovingTestObject::draw(Layer& renderTarget)
{
	renderTarget.getRenderTexture()->draw(texCoords, testTex);
}

void MovingTestObject::update(std::vector<int>& fkeyVec)
{
	//counter++;
	const float movement = 1;
	/*if (counter > 1 && counter < 10)
	{
		move(movement);
	}*/
	

	if(std::find(fkeyVec.begin(), fkeyVec.end(), sf::Keyboard::Up) != fkeyVec.end()) 
	{
		move(0, -movement);
	}
	if(std::find(fkeyVec.begin(), fkeyVec.end(), sf::Keyboard::Down) != fkeyVec.end()) 
	{
		move(0, movement);
	}
	if(std::find(fkeyVec.begin(), fkeyVec.end(), sf::Keyboard::Left) != fkeyVec.end()) 
	{
		move(-movement, 0);
	}
	if(std::find(fkeyVec.begin(), fkeyVec.end(), sf::Keyboard::Right) != fkeyVec.end()) 
	{
		move(movement, 0);
	}
}

void MovingTestObject::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
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
	texCoords[2].position = sf::Vector2f(position.x - texSize.x / 2, position.y - texSize.y / 2);	//top left
	texCoords[3].position = sf::Vector2f(position.x + texSize.x / 2, position.y - texSize.y / 2);	//top right


	texCoords[0].texCoords = sf::Vector2f(texSize.x, texSize.y);			//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, texSize.y);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(0, 0);			//top left
	texCoords[3].texCoords = sf::Vector2f(texSize.x, 0);	//top right

}

void MovingTestObject::write()
{
	//more INIParser stuff
}


sf::Vector2f* MovingTestObject::getPositionPtr()
{
	return &position;
}


void MovingTestObject::move(const sf::Vector2f& dist)
{
	position += dist;
	for (unsigned int i = 0; i < texCoords.getVertexCount(); i++)
	{
		texCoords[i].position += dist;
	}
}

void MovingTestObject::move(const float& dist_x, const float& dist_y)
{
	move(sf::Vector2f(dist_x, dist_y));
}
