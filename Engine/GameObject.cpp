#include "GameObject.h"

#include "AmrothUtils.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : Object(name)
{
	m_Transform = AddComponent(new Transform());

	if (!m_Name.empty())
	{
		Print("New ", TextColor::Green);
		Print(m_Name + "\n", TextColor::Yellow);
	}
}

GameObject::~GameObject()
{
	//UNDONE: Fix component removal at Destroy

	if (!m_Name.empty())
	{
		Print("(x) ", TextColor::Red);
		Print(m_Name, TextColor::Yellow);
		Print(" destroyed \n", TextColor::Red);
	}

	if (components.empty()) return;

	for (const auto* component : components)
	{
		if (component != nullptr)
			Destroy(*this, component);
	}
}

bool GameObject::IsActive() const
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