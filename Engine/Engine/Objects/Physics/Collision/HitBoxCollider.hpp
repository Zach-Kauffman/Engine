#pragma once
#include "HitBoxes\CircularHitbox.hpp"
#include "HitBoxes\AAHitbox.hpp"
#include "../../../Utility/Utilities.hpp"

class HitBoxCollider
{
public:
	HitBoxCollider();
	~HitBoxCollider();

    sf::Vector2f getNewPosition(HitBox* boxA, sf::Vector2f velA, HitBox* boxB, sf::Vector2f velB);
	bool checkCollision(HitBox* boxA, HitBox* boxB);

private:

	bool collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB);
	bool collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB);
	bool collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB);

	sf::Vector2f getCorVelDoubleAABB( sf::Vector2f vel, AAHitbox* boxA, AAHitbox* boxB);
	sf::Vector2f getCorVelCircAABB(sf::Vector2f vel, CircularHitbox* circA,  AAHitbox* boxB);
	sf::Vector2f getCorVelAABBCirc(sf::Vector2f vel, AAHitbox* boxB, CircularHitbox* circA)
	sf::Vector2f getCorVelDoubleCirc(sf::Vector2f vel, CircularHitbox* circA, CircularHitbox* circB);

    unsigned double distSq(sf::Vector2f vec);

    unsigned int orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r);

	AAHitbox* downcastAABB(HitBox* box);
	CircularHitbox* downcastCirc(HitBox* box);


	bool linesIntersect(const sf::Vector2f& p, const sf::Vector2f& r, const sf::Vector2f& q, const sf::Vector2f& s);

    const double knockback;
};

