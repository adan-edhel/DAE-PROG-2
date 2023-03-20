#pragma once
#include <vector>
#include "Object.h"

#include "Component.h"

class GameObject final : public Object
{
public:
	Transform* m_Transform;

	GameObject(const std::string& name);
	bool Active() const;
	void SetActive(const bool& active);
	~GameObject() override;

#pragma region Components
private:
	void RemoveComponent(Component* component)
	{
		components.erase(std::remove(components.begin(), components.end(), component), components.end());
	}

public:
	template<class T>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*>
	AddComponent(T* component)
	{
		auto* castComponentPtr{ dynamic_cast<Component*>(component) };

		castComponentPtr->m_GameObject = this;
		castComponentPtr->m_Transform = m_Transform;

		components.push_back(component);
		return component;
	}

	template <class T>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*>
	GetComponent()
	{
		for (auto* componentPtr : components)
		{
			T* castComponent{ dynamic_cast<T*>(componentPtr) };
			if (castComponent != nullptr)
				return castComponent;
		}

		return nullptr;
	}
#pragma endregion

private:
	friend Component;

	bool m_IsActive{ true };
	std::vector<Component*> components{};

	void Update(const float& deltaTime);
};
