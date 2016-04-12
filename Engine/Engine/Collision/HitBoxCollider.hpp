#pragma once
#include "HitBoxes\CircularHitbox.hpp"
#include "HitBoxes\AAHitbox.hpp"

class HitBoxCollider
{
public:
	HitBoxCollider();
	~HitBoxCollider();

	bool checkCollision(HitBox* boxA, HitBox* boxB);

private:

	bool collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB);
	bool collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB);
	bool collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB);

	AAHitbox* downcastAABB(HitBox* box);
	CircularHitbox* downcastCirc(HitBox* box);

};

