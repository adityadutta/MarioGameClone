#include "World.h"


World::World(Vector3& initialGravityAcceleration, Vector3& initialWindForce)
{
	gravityAcceleration = initialGravityAcceleration;
	windForce = initialWindForce;
}

void World::Update(double timeStep)
{
	Vector3 forceStar1;
	Vector3 forceStar2;
	for (auto body : bodies) {
		//Gravitation
		

		//Update position from velocity times timeStep
		//position = position(init) + linearVelocity * time + 0.5 * acceleration * time ^2
		body->position += body->linearVelocity * timeStep + (body->acceleration + gravityAcceleration) * 0.5 * timeStep * timeStep;

		//Update velocity from acceleration times timeStep
		//linearVelocity = linearVelocity(init) + acceleration * time;
		body->linearVelocity += (body->acceleration + gravityAcceleration) * timeStep;

		//setting acceleration to zero
		body->acceleration.SetZero();
	}

	//Force vector = force(mag) * direction vector(normalized)
	//direction vector(normalized) = PS/magnitude
	//Fg = G * Mp * Ms / r^2
	//update elapsed time by time step
	elapsedTime += timeStep;
}

void World::AddBody(gdBody* body)
{
	bodies.push_back(body);
}

World::~World()
{
	for (auto body : bodies) {
		delete body;
		body = nullptr;
	}
}
