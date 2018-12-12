#ifndef VECTOR3_H
#define VECTOR3_H

#include<string>
#include<sstream>
#include<math.h>

namespace MATH {
#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS (M_PI / 180.0f)
#endif	

#define VECTOR3_BACK	Vector3(0.0f, 0.0f, 1.0f)
#define VECTOR3_DOWN	Vector3(0.0f, -1.0f, 0.0f)
#define VECTOR3_FORWARD Vector3(0.0f, 0.0f, -1.0f)
#define VECTOR3_LEFT	Vector3(-1.0f, 0.0f, 0.0f)
#define VECTOR3_RIGHT	Vector3(1.0f, 0.0f, 0.0f)
#define VECTOR3_UP		Vector3(0.0f, 1.0f, 0.0f)
#define VECTOR3_BACK	Vector3(0.0f, 0.0f, 0.0f)


	struct Vector3
	{
		float x, y, z;

		Vector3();
		Vector3(float _x, float _y, float _z);

		float Length() const;				// return the length (magnitude) of the vector
		float LengthSquared() const;
		Vector3 Normalize() const;					// converts vector into the unit vector
		Vector3 Negate() const;

		Vector3 Add(const Vector3& V) const;
		float Dot(const Vector3& V) const;  // returns the dot product
		Vector3 Cross(const Vector3& V) const;
		Vector3 DivideBy(float a) const;
		Vector3 Multiply(float a) const;
		Vector3 Subtract(const Vector3& V) const;

		void Set(const Vector3& V);
		void Set(float _x, float _y, float _z);
		void SetZero();						// set x and y to zero

		static float Distance(const Vector3& V1, const Vector3& V2);

		inline const std::string ToString() const {
			std::stringstream stringStream;
			stringStream << "Vector3[ " << x << ", " << y << ", " << z << "]";
			return stringStream.str();
		}

		//overloading operators
		inline const Vector3 operator -() const			// negate vector. Const member can’t modify object
		{
			return Negate();
		}
		inline const Vector3 operator /(float rhs) const		// divide by a number "a"
		{
			return DivideBy(rhs);
		}
		inline const Vector3 operator *(float rhs) const		// multiply by a number "a"
		{
			return Multiply(rhs);
		}
		inline const Vector3 operator +(const Vector3& rhs) const	//add two vectors without changing values
		{
			return Add(rhs);
		}
		inline const Vector3 operator -(const Vector3& rhs) const
		{
			return Subtract(rhs);
		}
		inline const Vector3 operator += (const Vector3& rhs) // add a vector and assign. Using pass-by-const-reference
		{
			Set(Add(rhs));
			return *this;
		}
		inline const Vector3 operator -= (const Vector3& rhs) // subtract a vector to this vector
		{
			Set(Subtract(rhs));
			return *this;
		}
		inline const Vector3 operator *= (float rhs)		// multiply by a number “a” and set its value
		{
			Set(Multiply(rhs));
			return *this;
		}
		inline const Vector3 operator /= (float rhs)
		{
			Set(DivideBy(rhs));
			return *this;
		}
		inline const Vector3 operator = (const Vector3& rhs)
		{
			Set(rhs);
			return *this;
		}

		//friend function
		//multiplication is associative a*b = b*a
		//lhs * rhs 
		//float a;
		//a * vector
		//to overcome the ambiguity of the vector being on the rhs rather than on the lhs
		friend inline Vector3 operator * (float lhs, const Vector3& rhs)
		{
			return rhs.Multiply(lhs);
		}
	};
}
#endif //!VECTOR3_H

