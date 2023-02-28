#include "base.h"
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Vector3.h"

//-----------------------------------------------------------------
// Vector3 Constructors
//-----------------------------------------------------------------
Vector3::Vector3()
	:Vector3{ 0.0f, 0.0f, 0.0f }
{
}

Vector3::Vector3(float x, float y, float z)
	: x{ x }
	, y{ y }
	, z{ z }
{
}

Vector3::Vector3(const Point2f& fromPoint, const Point2f& tillPoint)
	: Vector3{ tillPoint.x - fromPoint.x, tillPoint.y - fromPoint.y, 0 }
{
}

Vector3::Vector3(const Point2f& point)
	: Vector3{ Point2f{ 0.0f, 0.0f }, point }
{
}


// -------------------------
// Methods
// -------------------------
bool Vector3::Equals(const Vector3& other, float epsilon) const
{
	return (abs(x - other.x) < epsilon)
		&& (abs(y - other.y) < epsilon)
		&& (abs(z - other.z) < epsilon);
}

Point2f Vector3::ToPoint2f() const
{
	return Point2f{ x, y };
}

float Vector3::DotProduct(const Vector3& other) const
{
	return x * other.x
		+ y * other.y
		+ z * other.z;
}

float Vector3::CrossProduct(const Vector3& other) const
{
	return (x * other.y) - (y * other.x);
}

std::string Vector3::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision(2);
	buffer << "Vector3(" << x << ", " << y << ", " << z << ")";
	return buffer.str();
}

float Vector3::Norm() const
{
	return Length();
}

float Vector3::Length() const
{
	return sqrt(SquaredLength());
}

float Vector3::SquaredLength() const
{
	return (x * x) + (y * y) + (z * z);
}

float Vector3::AngleWith(const Vector3& other) const
{
	//https://stackoverflow.com/questions/21483999/using-atan2-to-find-angle-between-two-vectors
	// not calling dot and cross functions to prevent the overhead
	return atan2((x * other.y) - (other.x * y), (x * other.x) + (y * other.y));
}

Vector3 Vector3::Normalized(float epsilon) const
{
	float length{ Length() };
	if (length < epsilon)
	{
		return Vector3{ 0, 0, 0};
	}
	else
	{
		return Vector3{ x / length, y / length, z / length };
	}
}

Vector3 Vector3::Orthogonal() const
{
	return Vector3{ -y, x , z};
}

Vector3 Vector3::Reflect(const Vector3& surfaceNormal) const
{
	return (*this) - 2 * (this->DotProduct(surfaceNormal) * surfaceNormal);
}

void Vector3::Set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

// -------------------------
// Member operators
// -------------------------
Vector3 Vector3::operator-() const
{
	return Vector3{ -x, -y, -z};
}
Vector3 Vector3::operator+ () const
{
	return Vector3{ x, y, z};
}

Vector3& Vector3::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector3& Vector3::operator/=(float rhs)
{
	*this *= 1 / rhs;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	*this += -rhs;
	return *this;
}

Vector3::operator Point2f()
{
	return Point2f{ x,y};
}

// -------------------------
// Non-member operators
// -------------------------
Vector3 operator*(float lhs, Vector3 rhs)
{
	return rhs *= lhs;
}

Vector3 operator*(Vector3 lhs, float rhs)
{
	return lhs *= rhs;
}

Vector3 operator/(Vector3 lhs, float rhs)
{
	return lhs *= (1 / rhs);
}

Vector3 operator+(Vector3 lhs, const Vector3& rhs)
{
	return lhs += rhs;
}

Vector3 operator-(Vector3 lhs, const Vector3& rhs)
{
	return lhs += -rhs;
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs.Equals(rhs));
}

bool operator!=(const  Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<< (std::ostream& lhs, const Vector3& rhs)
{
	lhs << rhs.ToString();
	return lhs;
}

// Point2f related operators
Point2f& operator+=(Point2f& lhs, const Vector3& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

Point2f operator+(Point2f lhs, const Vector3& rhs)
{
	lhs += rhs;
	return lhs;
}

Point2f& operator-=(Point2f& lhs, const Vector3& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

Point2f operator-(Point2f lhs, const Vector3& rhs)
{
	lhs -= rhs;
	return lhs;
}


//Vector3 operator-(const Point2f& lhs, const Point2f& rhs)
//{
//	Vector3 v{ lhs.x - rhs.x, lhs.y - rhs.y };
//	return v;
//}