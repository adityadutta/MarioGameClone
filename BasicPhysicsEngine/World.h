#ifndef WORLD_H
#define WORLD_H
#include"gdBody.h"
#include<vector>
#include"Vector3.h"

using namespace MATH;
class World
{
public:
	std::vector<gdBody*> bodies;										// A vector list of Body pointers
	double elapsedTime;
	Vector3 gravityAcceleration;
	Vector3 windForce;


	World(Vector3& initialGravityAcceleration, Vector3& initialWindForce); // The constructor
	~World();															 // The destructor. Delete the Body pointers
	void Update(double timeStep);										 // Update all the bodies
	void AddBody(gdBody* body);											 // Add a Body pointer to the vector list of bodies
};

#endif //!WORLD_H

