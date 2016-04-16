#include "Movable.hpp"

Movable::Movable(){}

Movable::Movable(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity, sf::Vector2f& newAcceleration)
{
	setPosition(newPosition);
	setVelocity(newVelocity);
	setAcceleration(newAcceleration);
	frameTimer.restart();
}

void Movable::updateMovement()
{
	double frameTime = frameTimer.restart().asSeconds();
	//HARDCODE REMOVE
	if (position.y > 1000)
	{
		velocity.y = 0;
		position.y = 1000;
	}
	
	if (air)
	{
		sf::Vector2f s = sf::Vector2f(sign(velocity.x), sign(velocity.y));
		sf::Vector2f air = sf::Vector2f(s.x * velocity.x * (s.x * util::clamp(abs(velocity.x), 10, 100)) * AIR, s.y * velocity.y * velocity.y * AIR);
		acceleration -= air;
	}

	velocity += sf::Vector2f(acceleration.x * frameTime, acceleration.y * frameTime);
	position += velocity;

	if (gravity)
	{
		acceleration = sf::Vector2f(0, GRAVITY);	//friction or something will go for x
	}
	else
	{
		acceleration = sf::Vector2f(0, 0);
	}

	if (velocity.x > maxSpeed)
	{
		//velocity.x = maxSpeed;
	}
	else if(velocity.x < maxSpeed*-1)
	{
		//velocity.x = maxSpeed*-1;
	}
}

void Movable::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

sf::Vector2f* Movable::getPosition()
{
	return &position;
}

void Movable::setVelocity(const sf::Vector2f& newVelocity)
{
	velocity = newVelocity;
}

sf::Vector2f* Movable::getVelocity()
{
	return &velocity;
}

void Movable::setAcceleration(const sf::Vector2f& newAcceleration)
{
	acceleration = newAcceleration;
}

sf::Vector2f* Movable::getAcceleration()
{
	return &acceleration;
}

void Movable::applyForce(const sf::Vector2f& force)
{
	acceleration += force;
}

void Movable::setMaxSpeed(const int& newMax)
{
	maxSpeed = newMax;
}

//private

int Movable::sign(const float& d)
{
	if (d >= 0){ return 1; }
	else{ return -1; }
}