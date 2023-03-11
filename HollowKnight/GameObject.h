#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class GameObject
	{
	public:
		Transform transform{};

		GameObject();
		bool isActive() const;
		void SetActive(const bool& active);
		~GameObject();

#pragma region Components
		void AddComponent(IComponent& component) { transform.AddComponent(&component); }
		void RemoveComponent(const IComponent& component) { transform.RemoveComponent(&component); }
		template<typename T>
		T* GetComponent() { return transform.GetComponent<T>(); }
#pragma endregion

	private:
		bool m_Active{ true };

		void Update(const float& deltaTime);
		void Draw() const;
	};
}
