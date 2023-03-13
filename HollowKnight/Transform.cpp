#include "pch.h"
#include "Transform.h"

Transform::Transform(bool& isActive) :
	m_pIsActive{ &isActive }
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

Transform::~Transform()
{
	for (auto const component : components)
	{
		delete component;
	}
}