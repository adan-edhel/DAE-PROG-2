#include "GameObject.h"

#include "Transform.h"

GameObject::GameObject(const std::string& name) : Object(name)
{
	m_Transform = AddComponent(new Transform());
}

GameObject::~GameObject()
{
	//UNDONE: Fix component removal at Destroy

	if (components.empty()) return;

	for (const auto* component : components)
	{
		if (component != nullptr)
			Destroy(component);
	}
}

bool GameObject::Active() const
{
	return m_IsActive;
}

void GameObject::SetActive(const bool& active)
{
	m_IsActive = active;
}

void GameObject::Update(const float& deltaTime)
{
	if (!m_IsActive) return;

	for ( const auto component : components)
	{
		component->Update(deltaTime);
	}
}