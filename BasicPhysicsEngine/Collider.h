#ifndef COLLIDER_H
#define COLLIDER_H
#include"Vector3.h"
#include"gdBody.h"
class Collider
{
public:
	Collider();
	~Collider();
	static bool CollisionCheck(const gdBody &body1, const gdBody &body2);
	static bool CollisionCheck(const gdBody &body1, const gdBody &body2, float _radius);
	static void HandleCollision(gdBody &body1, gdBody &body2, float _cor);
	static void HandleMovingCollision(gdBody &body1, gdBody &body2, float _cor);
};
#endif // !COLLIDER_H