#include "HitBoxCollider.hpp"


HitBoxCollider::HitBoxCollider()
{
}


HitBoxCollider::~HitBoxCollider()
{
}


bool HitBoxCollider::checkCollision(HitBox* boxA, HitBox* boxB)
{
	bool collided;

	if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::AABB))
	{
		collided = collideDoubleAABB(downcastAABB(boxA), downcastAABB(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::AABB))
	{
		collided = collideAABBCirc(downcastAABB(boxB), downcastCirc(boxA));
	}
	else if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::CIRC))
	{
		collided = collideAABBCirc(downcastAABB(boxA), downcastCirc(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::CIRC))
	{
		collided = collideDoubleCirc(downcastCirc(boxA), downcastCirc(boxB));
	}

	return collided;
}

//private

bool HitBoxCollider::collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB)
{
	enum boundpos { Top = 0, Right, Bot, Left, BOUND_SIZE};

	double boundsA[BOUND_SIZE];

	boundsA[Top] = boxA->getCorners().first.y;
	boundsA[Right] = boxA->getCorners().second.x;
	boundsA[Bot] = boxA->getCorners().second.y;
	boundsA[Left] = boxA->getCorners().first.x;

	double boundsB[BOUND_SIZE];

	boundsB[Top] = boxB->getCorners().first.y;
	boundsB[Right] = boxB->getCorners().second.x;
	boundsB[Bot] = boxB->getCorners().second.y;
	boundsB[Left] = boxB->getCorners().first.x;

	bool collided = true;

	if ((boundsA[Top] > boundsB[Bot]) || (boundsA[Bot] < boundsB[Top]) || (boundsA[Right] < boundsB[Left]) || (boundsA[Left] > boundsB[Right]))
	{
		collided = false;
	}

	return collided;

}

bool HitBoxCollider::collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB)
{

	enum cornerNames {TL = 0, TR, BR, BL, CORNER_SIZE};
	sf::Vector2f corners[CORNER_SIZE];
	corners[TL] = boxA->getCorners().first;
	corners[TR] = sf::Vector2f(boxA->getCorners().second.x, boxA->getCorners().first.y);
	corners[BR] = boxA->getCorners().second;
	corners[BL] = sf::Vector2f(boxA->getCorners().first.x, boxA->getCorners().second.y);

	bool distTest = false;
	for (unsigned int i = 0; i < CORNER_SIZE; i++)
	{
		if (boxB->isPointInside(corners[i]))
		{
			distTest = true;
			break;
		}
	}

	bool boxTest = false;
	if (!distTest)
	{
		

		AAHitbox testor;
		const sf::Vector2f circpos = boxB->getPosition();
		const double rad = boxB->getRadius();
		testor.setPosition(circpos);
		testor.setSize(sf::Vector2f(2 * rad, 2 * rad));

		boxTest = collideDoubleAABB(boxA, &testor);
		
	}

	return (boxTest || distTest);

	
}

bool HitBoxCollider::collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB)
{
	const double distX = boxA->getPosition().x - boxB->getPosition().x;
	const double distY = boxA->getPosition().y - boxB->getPosition().y;
	const double radsum = boxA->getRadius() + boxB->getRadius();

	return (fabs(distX * distX + distY * distY - radsum * radsum) < .001);
}

AAHitbox* HitBoxCollider::downcastAABB(HitBox* box)
{
	if (box->getType() == HitBox::AABB)
	{
		return (AAHitbox*)(box);
	}
}

CircularHitbox* HitBoxCollider::downcastCirc(HitBox* box)
{
	if (box->getType() == HitBox::CIRC)
	{
		return (CircularHitbox*)(box);
	}
}