#pragma once
#include "structs.h"

struct Vector3 final
{
	// -------------------------
	// Constructors 
	// -------------------------
	Vector3();
	explicit Vector3(float x, float y, float z = 0);
	explicit Vector3(const Point2f& fromPoint, const Point2f& tillPoint);
	explicit Vector3(const Point2f& point);

	// -------------------------
	// Member operators
	// -------------------------
	Vector3 operator-() const;
	Vector3 operator+() const;
	Vector3& operator*=(float rhs);
	Vector3& operator/=(float rhs);
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	explicit operator Point2f();

	// -------------------------
	// Methods
	// -------------------------
	// Convert to Point2f	
	Point2f	ToPoint2f() const;

	// Are two vectors equal within a threshold?				
	// u.Equals(v)
	bool Equals(const Vector3& other, float epsilon = 0.001f) const;

	// Convert to String 
	std::string	ToString() const;

	// DotProduct
	// float d = u.DotProduct(v);
	float DotProduct(const Vector3& other) const;

	// CrossProduct 
	// float d = u.CrossProduct(v);
	float CrossProduct(const Vector3& other) const;

	// Norm of a vector 
	// float l = v.Norm();
	float Norm() const;

	// Length of a vector: 
	// float l = v.Length();
	float Length() const;

	// Square Length of a vector.
	// Faster alternative for Length, sqrt is not executed. 
	float SquaredLength() const;

	// AngleWith returns the smallest angle with another vector within the range [-PI/2, PI/2]. 
	// A pos angle is counter clockwise from this to the other
	// float angle = u.AngleWith(v);
	float AngleWith(const Vector3& other) const;


	// Returns normalized form of a vector
	// Vector3 n = v.Normalized();
	Vector3 Normalized(float epsilon = 0.001f) const;

	// Returns the orthogonal of the Vector3
	// Vector3 w = v.Orthogonal();
	Vector3 Orthogonal() const;

	// Returns a vector that is the reflection of the Vector3
	// surfaceNormal: represents the normal of the surface at the reflection point
	Vector3 Reflect(const Vector3& surfaceNormal) const;

	// Sets the values of x and y
	void Set(float newX, float newY, float newZ);

	// -------------------------
	// Datamembers 
	// -------------------------
	float x;
	float y;
	float z;
};
// -------------------------
// Non member operators
// -------------------------
Vector3 operator*(float lhs, Vector3 rhs);
Vector3 operator*(Vector3 lhs, float rhs);
Vector3 operator/(Vector3 lhs, float rhs);

Vector3 operator+(Vector3 lhs, const Vector3& rhs);
Vector3 operator-(Vector3 lhs, const Vector3& rhs);

bool operator==(const Vector3& lhs, const Vector3& rhs);
bool operator!=(const  Vector3& lhs, const Vector3& rhs);

std::ostream& operator<< (std::ostream& lhs, const Vector3& rhs);

// Translating a point by a vector
Point2f& operator+=(Point2f& lhs, const Vector3& rhs);
Point2f operator+(Point2f lhs, const Vector3& rhs);

Point2f& operator-=(Point2f& lhs, const Vector3& rhs);
Point2f operator-(Point2f lhs, const Vector3& rhs);

// The difference vector between 2 points
//Vector3 operator-(const Point2f& lhs, const Point2f& rhs);

