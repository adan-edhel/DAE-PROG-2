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
		GameObject m_GameObject{};
		Transform* m_pTransform;
		Behavior();

	protected:
#pragma region Components
		IComponent* AddComponent(IComponent* component)
		{
			m_GameObject.AddComponent(component);
			return component;
		}
		void RemoveComponent(const IComponent* component) { m_GameObject.transform.RemoveComponent(component); }
		template<typename T>
		T* GetComponent() { return m_GameObject.transform.GetComponent<T>(); }
#pragma endregion
	};
}

