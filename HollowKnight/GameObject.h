#pragma once
#include "Transform.h"

class GameObject
{
public:
	Transform transform{ m_IsActive };

	GameObject();
	bool isActive() const;
	void SetActive(const bool& active);
	~GameObject();

#pragma region Components
	IComponent* AddComponent(IComponent* component)
	{
		transform.AddComponent(component);
		return component;
	}
	void RemoveComponent(const IComponent* component) { transform.RemoveComponent(component); }
	template<typename T>
	T* GetComponent() { return transform.GetComponent<T>(); }
#pragma endregion

private:
	bool m_IsActive{ true };

	void Update(const float& deltaTime);
	void Draw() const;
};