#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	AddComponent(new Transform());
	transform = GetComponent<Transform>();
}

GameObject::~GameObject()
{
	for (auto const component : components)
	{
		try
		{
			delete component;
		}
		catch (const std::exception&)
		{
			std::cout << "Components couldn't be cleared.";
		}
	}
}

GameObject* GameObject::GetReference()
{
	return this;
}

void GameObject::Update(float deltaTime)
{
	for (auto const component : components)
	{
		component->Update(deltaTime);
	}
}
