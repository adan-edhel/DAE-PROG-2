#include "Transform.h"

Transform::Transform()
{
}

void Transform::Translate(const Vector2& displacement)
{
	position += displacement;
}

void Transform::Translate(const float& x, const float& y)
{
	Translate(Vector2(x, y));
}