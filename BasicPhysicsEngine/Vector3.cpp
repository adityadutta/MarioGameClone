#include "Vector3.h"

using namespace MATH;

//default constructor for vector3
Vector3::Vector3()
{
	SetZero();
}

//parameterized constructor to pass in values to vector3
Vector3::Vector3(float _x, float _y, float _z)
{
	Set(_x, _y, _z);
}

//using pythagorean theorem to find length of vector
float Vector3::Length() const
{
	return sqrt(LengthSquared());
}

//using pythagorean theorem to find length of vector
float Vector3::LengthSquared() const 
{
	return (x*x + y*y + z*z);
}

//normalizing vector to 1
Vector3 Vector3::Normalize() const
{
	return DivideBy(Length());
}

//negating vector
Vector3 Vector3::Negate() const
{
	return Vector3(-x, -y, -z);
}

//adding two vector3
Vector3 Vector3::Add(const Vector3& V) const
{
	return Vector3(x + V.x, y + V.y, z + V.z);
}

//dot product of given vector
float Vector3::Dot(const Vector3& V) const
{
	float tempX, tempY, dotProduct;
	tempX = x * V.x;
	tempY = y * V.y;
	dotProduct = tempX + tempY;
	return dotProduct;
}

//cross product of given vector
Vector3 Vector3::Cross(const Vector3& V) const
{
	return Vector3(y * V.z - z * V.y,
		z * V.x - x * V.z,
		x * V.y - y * V.x);
}

//dividing vector3 by float a
Vector3 Vector3::DivideBy(float a) const
{
	return Vector3(x / a, y / a, z / a);
}

//multiplying  vector3 by float a
Vector3 Vector3::Multiply(float a) const
{
	return DivideBy(1 / a);
}

//sutracting two vector3
Vector3 Vector3::Subtract(const Vector3& V) const
{
	return Vector3(x - V.x, y - V.y, z - V.z);
}

//setting vector3 to another vector3
void Vector3::Set(const Vector3& V) 
{
	x = V.x;
	y = V.y;
	z = V.z;
}

//passing the parameters in the class
void Vector3::Set(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

//calling th set function to set the values to zero
void Vector3::SetZero()
{
	Set(0.0f, 0.0f, 0.0f);
}

float Vector3::Distance(const Vector3 &V1, const Vector3 &V2) {
	Vector3 r = V1 - V2;
	return(r.Length());
}


