#include "pch.h"
#include "Transform.h"

namespace AmrothFramework
{
	Transform::Transform()
	{
	}

	//Transform::Transform(Object* gameObject, Delegate<const float&>& updateDelegate)
	//{
	//	updateDelegate.Connect(gameObject , &Transform::Update);
	//}

	void Transform::Translate(const Vector2& displacement)
	{
		position += displacement;
	}

	void Transform::Translate(const float& x, const float& y)
	{
		Translate(Vector2(x, y));
	}

	void Transform::Update(const float& deltaTime) const
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
}