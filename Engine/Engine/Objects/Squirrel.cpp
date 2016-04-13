#include "squirrel.hpp"

using namespace objects;

Squirrel::Squirrel()
{
	size = sf::Vector2f(100, 100);
	moveSpeed = 10;
}

Squirrel::~Squirrel(){}

void Squirrel::draw(Layer& renderTarget)
{
	if (!isActive){return;}

	if (velocity.x > 0 || velocity.y > 0)
	{
		//sf::RenderTexture* renderTex = renderTarget.getRenderTexture();
		walking.drawNextFrame(*renderTarget.getRenderTexture());
	}
	else
	{
		idle.drawNextFrame(*renderTarget.getRenderTexture()); 
	}
}

void Squirrel::update(InputData& inpData)
{
	if (!isActive){ return; }

	if (inpData.isKeyHeld(sf::Keyboard::Up))
	{
		applyForce(sf::Vector2f(0, -moveSpeed));
	}
	if (inpData.isKeyHeld(sf::Keyboard::Down))
	{
		applyForce(sf::Vector2f(0, moveSpeed));;
	}
	if (inpData.isKeyHeld(sf::Keyboard::Left))
	{
		applyForce(sf::Vector2f(-moveSpeed, 0));
	}
	if (inpData.isKeyHeld(sf::Keyboard::Right))
	{
		applyForce(sf::Vector2f(moveSpeed, 0));
	}

	Movable::update();
}

void Squirrel::load(boost::property_tree::ptree& dataTree, ResourceManager& recMan)
{
	XMLParser reader;
	walkingSSName = reader.readValue<std::string>("walking", dataTree);
	idleSSName = reader.readValue<std::string>("idle", dataTree);
	fps = reader.readValue<int>("fps", dataTree);
	moveSpeed = reader.readValue<int>("moveSpeed", dataTree);
	position.x = reader.readValue<float>("position.<xmlattr>.x", dataTree);
	position.y = reader.readValue<float>("position.<xmlattr>.y", dataTree);
	size.x = reader.readValue<float>("size.<xmlattr>.x", dataTree);
	size.y = reader.readValue<float>("size.<xmlattr>.y", dataTree);

	walking = Animation(recMan.getTexturePointerByName(walkingSSName), size, fps, position);
	idle = Animation(recMan.getTexturePointerByName(idleSSName), size, fps, position);
}

boost::property_tree::ptree Squirrel::write()
{
	boost::property_tree::ptree xml;
	xml.put("walking", walkingSSName);
	xml.put("idle", idleSSName);
	xml.put("fps", fps);
	xml.put("moveSpeed", moveSpeed);
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", size.x);
	xml.put("size.<xmlattr>.y", size.y);

	return xml;
}