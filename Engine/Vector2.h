#pragma once
#include "structs.h"

struct Vector2 final
{
	// -------------------------
	// Constructors 
	// -------------------------
	Vector2();
	explicit Vector2(float x, float y);
	explicit Vector2(const Point2f& fromPoint, const Point2f& tillPoint);
	explicit Vector2(const Point2f& point);

	// -------------------------
	// Member operators
	// -------------------------
	Vector2 operator-() const;
	Vector2 operator+() const;
	Vector2& operator*=(float rhs);
	Vector2& operator/=(float rhs);
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	explicit operator Point2f();

	// -------------------------
	// Methods
	// -------------------------
	// Convert to Point2f	
	Point2f	ToPoint2f() const;

	// Are two vectors equal within a threshold?				
	// u.Equals(v)
	bool Equals(const Vector2& other, float epsilon = 0.001f) const;

	// Convert to String 
	std::string	ToString() const;

	// DotProduct
	// float d = u.DotProduct(v);
	float DotProduct(const Vector2& other) const;

	// CrossProduct 
	// float d = u.CrossProduct(v);
	float CrossProduct(const Vector2& other) const;

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
	// A s_Position angle is counter clockwise from this to the other
	// float angle = u.AngleWith(v);
	float AngleWith(const Vector2& other) const;

	// Returns normalized form of a vector
	// Vector2 n = v.Normalized();
	Vector2 Normalized(float epsilon = 0.001f) const;

	// Returns the orthogonal of the Vector2
	// Vector2 w = v.Orthogonal();
	Vector2 Orthogonal() const;

	// Returns a vector that is the reflection of the Vector2
	// surfaceNormal: represents the normal of the surface at the reflection point
	Vector2 Reflect(const Vector2& surfaceNormal) const;

	// Sets the values of x and y
	void Set(float newX, float newY);

	// -------------------------
	// Datamembers 
	// -------------------------
	float x;
	float y;
};
// -------------------------
// Non member operators
// -------------------------
Vector2 operator*(float lhs, Vector2 rhs);
Vector2 operator*(Vector2 lhs, float rhs);
Vector2 operator/(Vector2 lhs, float rhs);

Vector2 operator+(Vector2 lhs, const Vector2& rhs);
Vector2 operator-(Vector2 lhs, const Vector2& rhs);

bool operator==(const Vector2& lhs, const Vector2& rhs);
bool operator!=(const  Vector2& lhs, const Vector2& rhs);

std::ostream& operator<< (std::ostream& lhs, const Vector2& rhs);

// Translating a point by a vector
Point2f& operator+=(Point2f& lhs, const Vector2& rhs);
Point2f operator+(Point2f lhs, const Vector2& rhs);

Point2f& operator-=(Point2f& lhs, const Vector2& rhs);
Point2f operator-(Point2f lhs, const Vector2& rhs);

// The difference vector between 2 points
Vector2 operator-(const Point2f& lhs, const Point2f& rhs);