#include "gdBody.h"

gdBody::gdBody(double _mass)
{
	mass = _mass;
}

//constructor to pass values in the class
gdBody::gdBody(char* _imageName, double _mass, Vector3 _position, Vector3 _linearVelocity, Vector3 _acceleration)
{
	mass = _mass;
	position = _position;
	linearVelocity = _linearVelocity;
	acceleration = _acceleration;
	bodyImage = IMG_Load(_imageName);
	if (bodyImage == nullptr) {
		/// What should we do?
	}
}
void gdBody::Update(double timeStep)
{

	//Update position from velocity times timeStep
	//position = position(init) + linearVelocity * time + 0.5 * acceleration * time ^2
	position += linearVelocity * timeStep + acceleration * 0.5 * timeStep * timeStep;

	//Update velocity from acceleration times timeStep
	//linearVelocity = linearVelocity(init) + acceleration * time;
	linearVelocity += acceleration * timeStep;


	acceleration.SetZero();
}


void gdBody::ApplyForceToCentre(const Vector3& force)
{
	//a = f/m
	Vector3 temp(force);
	acceleration = temp / mass;
}

SDL_Surface* gdBody::getImage() {
	return bodyImage;
}

void gdBody::SetImage(char* _imageName) {
	bodyImage = IMG_Load(_imageName);
	if (bodyImage == nullptr) {
		/// What should we do?
	}
}


double gdBody::getMass() {
	return mass;
}