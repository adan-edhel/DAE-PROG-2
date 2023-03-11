#pragma once
#include "GameStructs.h"
#include "IComponent.h"
#include "Vector2.h"
#include <iostream>
#include <vector>



namespace AmrothFramework
{
	class Transform
	{
	public:
		Tag tag{ Tag::Default };

		Vector2 position{};
		Vector2 rotation{};
		Vector2 scale{};

		Transform();
		//Transform(GameObject* gameObject, Delegate<const float&>& updateDelegate);
		void Translate(const Vector2& displacement);
		void Translate(const float& x, const float& y);
		void Update(const float& deltaTime) const;
		~Transform();

#pragma region Components
		// Adds new component
		IComponent* AddComponent(IComponent* component)
		{
			component->m_Transform = this;
			components.push_back(component);
			return component;
		}

		// Removes existing component
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

		// Returns an existing component
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

	private:
		// List of added components
		std::vector<IComponent*> components{};
#pragma endregion Components

	};
}
