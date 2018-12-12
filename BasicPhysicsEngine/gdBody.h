#ifndef GDBODY_H
#define GDBODY_H

#include<SDL.h>
#include<SDL_image.h>
#include"Vector3.h"

using namespace MATH;
class gdBody
{
	double mass;									//variable to hold the value of mass
	SDL_Surface *bodyImage;
public:
	Vector3 position;								//variable to hold the value of position
	Vector3 linearVelocity;							//variable to hold the value of velocity
	Vector3 acceleration;							//variable to hold the value of acceleration

	gdBody(double _mass);
	gdBody(char* _imageName, double _mass, Vector3 _position, Vector3 _linearVelocity, Vector3 _acceleration);
	void Update(double timeStep);
	void ApplyForceToCentre(const Vector3& force);   // update acceleration using a = F/m
	SDL_Surface* getImage();
	double getMass();
	void SetImage(char* _imageName);

};
#endif //!GDBODY_H