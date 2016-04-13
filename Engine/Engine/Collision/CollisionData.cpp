#include "CollisionData.hpp"


CollisionData::CollisionData()
{
}


CollisionData::~CollisionData()
{
}

void CollisionData::setMass(const double& m)
{
    mass = m;
}

double CollisionData::getMass()

{
    return mass;
}

void CollisionData::setIsStationary(const bool& stat)
{
    isStationary = stat;
}

bool CollisionData::getIsStationary()
{
    return stat;
}

void CollisionData::setPosition(const sf::Vector2f& pos)
{
    position = pos;
}
void CollisionData::changePosition(const sf::Vector2f& dpos)
{
    position += dpos;
}

sf::Vector2f CollisionData::getPosition()
{
    return position;
}

void CollisionData::setVelocity(const sf::Vector2f& vel)
{
    velocity = vel;
}

void CollisionData::changeVelocity(const sf::Vector2f& dvel)
{
    velocity += dvel;
}

sf::Vector2f CollisionData::getVelocity()
{
    return velocity;
}

void CollisionData::setAcceleration(const sf::Vector2f& accel)
{
    acceleration = accel;
}

void CollisionData::changeAcceleration(const sf::Vector2f& daccel)
{
    acceleration += daccel;
}

sf::Vector2f CollisionData::getAcceleration()
{
    return acceleration;
}
