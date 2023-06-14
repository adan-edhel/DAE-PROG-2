#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include "Vector2.h"

//-----------------------------------------------------------------
// Vector2 Constructors
//-----------------------------------------------------------------
Vector2::Vector2()
	:Vector2{ 0.0f, 0.0f }
{
}

Vector2::Vector2(float x, float y)
	: x{ x }
	, y{ y }
{
}

Vector2::Vector2(const Point2f& fromPoint, const Point2f& tillPoint)
	: Vector2{ tillPoint.x - fromPoint.x, tillPoint.y - fromPoint.y }
{
}

Vector2::Vector2(const Point2f& point)
	: Vector2{ Point2f{ 0.0f, 0.0f }, point }
{
}

// -------------------------
// Methods
// -------------------------
bool Vector2::Equals(const Vector2& other, float epsilon) const
{
	return (abs(x - other.x) < epsilon) && (abs(y - other.y) < epsilon);
}

Point2f Vector2::ToPoint2f() const
{
	return Point2f{ x, y };
}

float Vector2::DotProduct(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::CrossProduct(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

std::string Vector2::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision(2);
	buffer << x << ", " << y;
	return buffer.str();
}

std::string Vector2::ToRoundedString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision(0);
	buffer << x << ", " << y;
	return buffer.str();
}

float Vector2::Norm() const
{
	return Length();
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::SquaredLength() const
{
	return x * x + y * y;
}

float Vector2::AngleWith(const Vector2& other) const
{
	//https://stackoverflow.com/questions/21483999/using-atan2-to-find-angle-between-two-vectors
	// not calling dot and cross functions to prevent the overhead
	return atan2(x * other.y - other.x * y, x * other.x + y * other.y);
}

Vector2 Vector2::Normalized(float epsilon) const
{
	float length{ Length() };
	if (length < epsilon)
	{
		return Vector2{ 0, 0 };
	}
	else
	{
		return Vector2{ x / length, y / length };
	}
}

Vector2 Vector2::Orthogonal() const
{
	return Vector2{ -y, x };
}

Vector2 Vector2::Reflect(const Vector2& surfaceNormal) const
{
	return (*this) - 2 * (this->DotProduct(surfaceNormal) * surfaceNormal);
}

void Vector2::MoveTowards(Vector2& current, const Vector2& target, const float& maxDelta)
{
	Vector2 direction;
	direction.x = target.x - current.x;
	direction.y = target.y - current.y;

	const float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance <= maxDelta)
		current = target;
	else
	{
		const float ratio = maxDelta / distance;
		Vector2 newPosition;
		newPosition.x = current.x + direction.x * ratio;
		newPosition.y = current.y + direction.y * ratio;
		current = newPosition;
	}
}

void Vector2::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

// -------------------------
// Member operators
// -------------------------
Vector2 Vector2::operator-() const
{
	return Vector2{ -x, -y };
}
Vector2 Vector2::operator+ () const
{
	return Vector2{ x, y };
}

Vector2& Vector2::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2& Vector2::operator/=(float rhs)
{
	*this *= 1 / rhs;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	*this += -rhs;
	return *this;
}

Vector2::operator Point2f()
{
	return Point2f{ x,y };
}

// -------------------------
// Non-member operators
// -------------------------
Vector2 operator*(float lhs, Vector2 rhs)
{
	return rhs *= lhs;
}

Vector2 operator*(Vector2 lhs, float rhs)
{
	return lhs *= rhs;
}

Vector2 operator/(Vector2 lhs, float rhs)
{
	return lhs *= (1 / rhs);
}

Vector2 operator+(Vector2 lhs, const Vector2& rhs)
{
	return lhs += rhs;
}

Vector2 operator-(Vector2 lhs, const Vector2& rhs)
{
	return lhs += -rhs;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	return (lhs.Equals(rhs));
}

bool operator!=(const  Vector2& lhs, const Vector2& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<< (std::ostream& lhs, const Vector2& rhs)
{
	lhs << rhs.ToString();
	return lhs;
}

// Point2f related operators
Point2f& operator+=(Point2f& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

Point2f operator+(Point2f lhs, const Vector2& rhs)
{
	lhs += rhs;
	return lhs;
}

Point2f& operator-=(Point2f& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

Point2f operator-(Point2f lhs, const Vector2& rhs)
{
	lhs -= rhs;
	return lhs;
}


Vector2 operator-(const Point2f& lhs, const Point2f& rhs)
{
	Vector2 v{ lhs.x - rhs.x, lhs.y - rhs.y };
	return v;
}