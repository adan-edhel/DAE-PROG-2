#pragma once
#include "GameObject.h"

namespace AmrothFramework
{
	class Animator;
	class Rigidbody2D;
	class SpriteRenderer;

	class Behavior
	{
	public:
		GameObject gameObject{};
		Transform* transform;
		Behavior();

	protected:
#pragma region Components
		IComponent* AddComponent(IComponent* component)
		{
			gameObject.AddComponent(component);
			return component;
		}
		void RemoveComponent(const IComponent* component) { gameObject.transform.RemoveComponent(component); }
		template<typename T>
		T* GetComponent() { return gameObject.transform.GetComponent<T>(); }
#pragma endregion
	};
}

