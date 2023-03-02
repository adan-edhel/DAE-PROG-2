#pragma once
#include <vector>
#include "IComponent.h"
#include "Transform.h"
#include <iostream>

class GameObject
{
public:
	GameObject();
	~GameObject();

#pragma region Components
	template<typename T>
	T* GetComponent()
	{
		for (auto component : components)
		{
			try
			{
				T* t = dynamic_cast<T*>(component);
				if (t)
				{
					return t;
				}
			}
			catch (const std::bad_cast&)
			{
				std::cout << "Component not found. \n";
			}
		}
		return nullptr;
	}

	void AddComponent(IComponent* component)
	{
		components.push_back(component);
	}

	void RemoveComponent(const IComponent* component)
	{
		// Find the component in the vector
		auto it = std::find(components.begin(), components.end(), component);

		// If the component is found, remove it
		if (it != components.end())
		{
			components.erase(it);
			// Free the memory of the component
			delete component;
		}
	}
#pragma endregion Components
	
	Transform* transform{};

protected:
	GameObject* GetReference();
	virtual void Update(float deltaTime);

private:
	std::vector<IComponent*> components{};
};

