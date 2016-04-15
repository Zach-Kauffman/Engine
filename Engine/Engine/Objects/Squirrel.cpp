#include "squirrel.hpp"

using namespace objects;

Squirrel::Squirrel()
{
	displaySize = sf::Vector2f(100, 100);
	moveSpeed = 10;
}

Squirrel::~Squirrel(){}

void Squirrel::draw(Layer& renderTarget)
{
	if (!isActive){return;}

	if (abs(velocity.x) > 0 || velocity.y > 0)
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

	updateMovement();
}

void Squirrel::load(boost::property_tree::ptree& dataTree, ResourceManager& recMan)
{
	XMLParser reader;
	walkingSSName = reader.readValue<std::string>("walking", dataTree);
	idleSSName = reader.readValue<std::string>("idle", dataTree);
	fps = reader.readValue<int>("fps", dataTree);
	moveSpeed = reader.readValue<float>("moveSpeed", dataTree);
	position.x = reader.readValue<float>("position.<xmlattr>.x", dataTree);
	position.y = reader.readValue<float>("position.<xmlattr>.y", dataTree);
	displaySize.x = reader.readValue<float>("size.<xmlattr>.x", dataTree);
	displaySize.y = reader.readValue<float>("size.<xmlattr>.y", dataTree);
	frameSize.x = reader.readValue<float>("frameSize.<xmlattr>.x", dataTree);
	frameSize.y = reader.readValue<float>("frameSize.<xmlattr>.y", dataTree);

	walking = Animation(recMan.getTexturePointerByName(walkingSSName), frameSize, displaySize, fps, position);
	idle = Animation(recMan.getTexturePointerByName(idleSSName), frameSize, displaySize, fps, position);
	setMaxSpeed(5);
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
	xml.put("size.<xmlattr>.x", displaySize.x);
	xml.put("size.<xmlattr>.y", displaySize.y);
	xml.put("frameSize.<xmlattr>.x", frameSize.x);
	xml.put("frameSize.<xmlattr>.y", frameSize.y);


	return xml;
}