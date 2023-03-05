#include "pch.h"
#include "Transform.h"

#include "Rigidbody2D.h"
#include "SpriteRenderer.h"

Transform::Transform()
{
	AddComponent(new SpriteRenderer(this));
	AddComponent(new Rigidbody2D(this));
}

void Transform::Translate(const Vector2& displacement)
{
	position += displacement;
}

void Transform::Translate(const float& x, const float& y)
{
	Translate(Vector2(x, y));
}

void Transform::Update(const float& deltaTime)
{
	for (auto const component : components)
	{
		component->Update(deltaTime);
	}
}

Transform::~Transform()
{
	for (auto const component : components)
	{
		delete component;
	}
}