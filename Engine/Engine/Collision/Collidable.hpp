#pragma once
#include "HitBoxes\HitBox.hpp"
#include <boost\shared_ptr.hpp>
#include "CollisionData.hpp"
class Collidable
{
public:
	Collidable();
	~Collidable();


	void setColliding(const bool& col);
	bool getColliding();

	CollisionData* getCollisionData();
	virtual void recieveCollisionData(CollisionData*) = 0;

protected:
	boost::shared_ptr<HitBox> hitbox;
	CollisionData colData;
	bool colliding;
};

