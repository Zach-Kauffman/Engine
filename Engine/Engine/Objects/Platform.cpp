#include "Platform.hpp"

using namespace objects;

Platform::Platform()
{
    colliding = true;
	isActive = false;
	movable = false;
	gravity = false;
	//air = false;
}

Platform::~Platform(){}


void Platform::draw(Layer& renderTarget)
{
	if (!isActive){ return; }
	tex.update();
	tex.draw(*renderTarget.getRenderTexture());
	hitbox.updatePosition();
}		//renders object to given sf::RenderTexture&


void Platform::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
{
	bool hasBottom = true;
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);
	parser.readValue<bool>("hasBottom", hasBottom, dataTree);

	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);
	sf::Texture* platformTexture = resources.getTexturePointerByName(textureName);

	tex = Texture(platformTexture, &position, &size);

	HitBox box;
	hitbox.create(size);
	hitbox.setPosition(position);
	hitbox.setHasBottom(hasBottom);

	setHitBox(hitbox);

}


boost::property_tree::ptree Platform::write()
{
	boost::property_tree::ptree xml;
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", size.x);
	xml.put("size.<xmlattr>.y", size.y);
	xml.put("texture", textureName);
	xml.put("hasBottom", hitbox.hasBottom());
	xml.put("type", type);
	return xml;
}

