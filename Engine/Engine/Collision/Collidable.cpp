#include "Collidable.hpp"


Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}


void Collidable::setColliding(const bool& col)
{
	colliding = col;
}

bool Collidable::getColliding()
{
	return colliding;
}

CollisionData* Collidable::getCollisionData()
{
	return &colData;
}

