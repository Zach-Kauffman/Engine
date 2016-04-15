#pragma once
#include <SFML\Graphics.hpp>
class CollisionData
{
public:
	CollisionData();
	~CollisionData();

	void setMass(const double& m);
	double getMass();

	void setIsStationary(const bool& stat);
	bool getIsStationary();

	void setPosition(const sf::Vector2f& pos);
	void changePosition(const sf::Vector2f& dpos);
	sf::Vector2f getPosition();

    void setVelocity(const sf::Vector2f& vel);
    void changeVelocity(const sf::Vector2f& dvel);
	sf::Vector2f getVelocity();

    void setAcceleration(const sf::Vector2f& accel);
    void changeAcceleration(const sf::Vector2f& daccel);
	sf::Vector2f getAcceleration();

	void update();




private:

	//double damage;
	double mass;
	bool isStationary;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;



};

