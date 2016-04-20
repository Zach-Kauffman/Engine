#pragma once
#include "../../../Utility/Utilities.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collidable.hpp"
#include "CollisionData.hpp"

class Collider
{
public:
	typedef std::vector<sf::Vector2f> polygon;

	Collider();
	~Collider();

	static CollisionData collide(Collidable* o1, Collidable* o2);
	static CollisionData collide(Collidable* o1, std::vector<Collidable*>& oVec);
	static CollisionData collide(HitBox& b1, HitBox& b2);
	static CollisionData collide(HitBox& b1, std::vector<HitBox*>& b2);

	static	std::tuple<sf::Vector2f, sf::Vector2f, bool> Collider::getKineticResponseDoublePolygon(const sf::Vector2f& vel, const polygon& polyA, const polygon& polyB);

private:

	static std::pair<sf::Vector2f, bool> getLinePoint(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b);
	static bool checkPointOnLine(const sf::Vector2f& point, const sf::Vector2f& pa, const sf::Vector2f& vec);
	static std::pair<sf::Vector2f, sf::Vector2f> getBoundingBoxCorners(const std::vector<sf::Vector2f>& points);
	static bool isCollide(const std::vector<sf::Vector2f>& hb1, const std::vector<sf::Vector2f>& hb2);

	static double magSq(const sf::Vector2f& vec);
	static double distSq(const sf::Vector2f& veca, const sf::Vector2f& vecb);

	static bool checkBoundingBoxCollision(const sf::Vector2f& tla, const sf::Vector2f& bra, const sf::Vector2f& tlb, const sf::Vector2f& brb);

	static sf::Vector3f crossProductZN(const sf::Vector2f& v, const sf::Vector2f& u);
	static sf::Vector3f crossProduct(const sf::Vector3f& v, const sf::Vector3f& u);
	static double dotProduct(const sf::Vector2f& v, const sf::Vector2f& u);

};


