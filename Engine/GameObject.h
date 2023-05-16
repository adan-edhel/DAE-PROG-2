#pragma once
#include "Object.h"
#include "IUpdatable.h"

#include "Component.h"
#include <vector>

#include "AmrothUtils.h"

class GameObject final : public Object, public IUpdatable
{
public:
	Transform* m_Transform;

	GameObject(const std::string& name = "");
	bool IsActive() const;
	void SetActive(const bool& active);
	~GameObject() override;

#pragma region Components
private:
	void RemoveComponent(Component* component)
	{
		components.erase(std::remove(components.begin(), 
									 components.end(), component), 
									 components.end());
	}

public:
	template<class T>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*>
	AddComponent(T* component)
	{
		auto* castComponentPtr{ dynamic_cast<Component*>(component) };

		if (!castComponentPtr->m_Name.empty() && !m_Name.empty())
		{	
			Print("New ", TextColor::Green);
			Print(castComponentPtr->m_Name, TextColor::Lightblue);
			Print(" on ");
			Print(m_Name + "\n", TextColor::Yellow);
		}

		castComponentPtr->Initialize(this);
		castComponentPtr->Awake();
		castComponentPtr->Start();

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

	template <class T = Component>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> result;
		for (auto* componentPtr : components)
		{
			T* castComponent{ dynamic_cast<T*>(componentPtr) };
			if (castComponent != nullptr)
				result.push_back(castComponent);
		}
		return result;
	}
#pragma endregion

private:
	bool m_IsActive{ true };
	std::vector<Component*> components{};

	void Update(const float& deltaTime) override;
};