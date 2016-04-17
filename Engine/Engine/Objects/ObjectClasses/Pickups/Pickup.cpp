#include "Pickup.hpp"

using namespace objects;

Pickup::Pickup()
{
	removed = false;
}


Pickup::~Pickup()
{
}




void Pickup::draw(Layer& renderTarget)
{
	if (!removed)
	{
		renderTarget.getRenderTexture()->draw(textureCoords, pickupTexture);
	}
	
}

void Pickup::update(InputData& inpData)
{
	if (!removed)
	{
		//if (/*getCollidingWithSquirrel*/)
		//{
		//	removed = true;
		//}
	}
}

void Pickup::load(boost::property_tree::ptree& dataTree, ResourceManager& rman)
{
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);
	parser.readValue<std::string>("season_name", seasonName, dataTree);
	parser.readValue<std::string>("pickup_name", pickupName, dataTree);

	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);

	pickupTexture = rman.getTexturePointerByName(textureName);
	
	sf::Vector2f texSize = (sf::Vector2f)(pickupTexture->getSize());

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


	pdata.load(pickupName);



}

 boost::property_tree::ptree Pickup::write()
{
	boost::property_tree::ptree properties;
	properties.put("position.<xmlattr>.x", position.x);
	properties.put("position.<xmlattr>.y", position.y);
	properties.put("size.<xmlattr>.x", size.x);
	properties.put("size.<xmlattr>.y", size.y);
	properties.put("season_name", seasonName);
	properties.put("pickup_name", pickupName);
	properties.put("texture", textureName);

	return properties;
}

 bool Pickup::isRemoved()
 {
	 return removed;
 }

 PickupData Pickup::getPickupData()
 {
	 return pdata;
 }