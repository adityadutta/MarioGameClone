#include "Collider.h"
#include"Vector3.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::CollisionCheck(const gdBody &body1, const gdBody &body2, float _radius)
{
	
	if (Vector3::Distance(body1.position, Vector3(body2.position.x + 10.0f, body2.position.y - 2.0f, body2.position.z)) <  _radius) {
		return true;
	}
	return false;
}

bool Collider::CollisionCheck(const gdBody &body1, const gdBody &body2)
{
	if ( Vector3::Distance(body1.position, body2.position) < 3.8f) {
		return true;
	}
	return false;
}
void Collider::HandleCollision(gdBody &body1, gdBody &body2, float _cor)
{
		Vector3 normal = (body2.position - body1.position).Normalize();

		Vector3 projection = (-body1.linearVelocity.Dot(normal)) * normal;

		body1.linearVelocity += 2 * projection * _cor;
}
void Collider::HandleMovingCollision(gdBody &body1, gdBody &body2, float _cor)
{
	Vector3 normal = (body2.position - body1.position).Normalize();

	float initVelocity1 = body1.linearVelocity.Dot(normal);
	float initVelocity2 = body2.linearVelocity.Dot(normal);

	float finVelocity1 = (((body1.getMass() - _cor * body2.getMass()) * initVelocity1) + ((1.0f + _cor) * body2.getMass() * initVelocity2)) / (body1.getMass() + body2.getMass());
	float finVelocity2 = (((body2.getMass() - _cor * body1.getMass()) * initVelocity2) + ((1.0f + _cor) * body1.getMass() * initVelocity1)) / (body1.getMass() + body2.getMass());

	body1.linearVelocity = ((finVelocity1 - initVelocity1) * normal);
	body2.linearVelocity = ((finVelocity2 - initVelocity2) * normal);
}