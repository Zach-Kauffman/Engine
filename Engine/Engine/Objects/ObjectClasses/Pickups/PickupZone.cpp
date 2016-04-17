#include "PickupZone.hpp"

using namespace objects;

PickupZone::PickupZone()
{
	displaying = true;
}


PickupZone::~PickupZone()
{
}


void PickupZone::draw(Layer& renderTarget)
{
	if (displaying)
	{
		renderTarget.getRenderTexture()->draw(textureCoords, pZoneTexture);
	}
}

void PickupZone::update(InputData& inpData)
{

}

void PickupZone::load(boost::property_tree::ptree& dataTree, ResourceManager& rman)
{
	XMLParser parser;
	parser.readValue<double>("y_value", yVal, dataTree);	//loading x coord
	parser.readValue<double>("x_value_left", xValLeft, dataTree);	//loading y coord
	parser.readValue<double>("x_value_right", xValRight, dataTree);
	parser.readValue<std::string>("season_name", seasonName, dataTree);

	const sf::Vector2f size(xValRight - xValLeft, 6);
	const sf::Vector2f position((xValRight + xValLeft) / 2, yVal + 3);
	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);

	pZoneTexture = rman.getTexturePointerByName(textureName);
	
	sf::Vector2f texSize = (sf::Vector2f)(pZoneTexture->getSize());

	textureCoords = sf::VertexArray(sf::Quads, 4); 

	//defining edge coordinates centered on position
	if (size.x + size.y == 0)
	{
		textureCoords[0].position = sf::Vector2f(position.x + texSize.x / 2, position.y + texSize.y / 2);	//bottom right
		textureCoords[1].position = sf::Vector2f(position.x - texSize.x / 2, position.y + texSize.y / 2);	//bottom left
		textureCoords[2].position = sf::Vector2f(position.x - texSize.x / 2, position.y - texSize.y / 2);	//top left
		textureCoords[3].position = sf::Vector2f(position.x + texSize.x / 2, position.y - texSize.y / 2);	//top right
	}
	else
	{
		textureCoords[0].position = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);	//bottom right
		textureCoords[1].position = sf::Vector2f(position.x - size.x / 2, position.y + size.y / 2);	//bottom left
		textureCoords[2].position = sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2);	//top left
		textureCoords[3].position = sf::Vector2f(position.x + size.x / 2, position.y - size.y / 2);	//top right
	}
	

	//defining texture mapping coords
	textureCoords[0].texCoords = sf::Vector2f(texSize.x, texSize.y);			//bottom right
	textureCoords[1].texCoords = sf::Vector2f(0, texSize.y);					//bottom left
	textureCoords[2].texCoords = sf::Vector2f(0, 0);			//top left
	textureCoords[3].texCoords = sf::Vector2f(texSize.x, 0);	//top right


}


boost::property_tree::ptree PickupZone::write()
{
	boost::property_tree::ptree properties;
	properties.put("y_value", yVal);
	properties.put("x_value_left", xValLeft);
	properties.put("x_value_right", xValLeft); 
	properties.put("season_name", seasonName);
	properties.put("texture", textureName);

	return properties;
}

Pickup generatePickup()
{
	
}

void createDistribution()
{
	int sum = 0;

}