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
	if (!m_Name.empty())
	{
		Print("(x) ", TextColor::Red);
		Print(m_Name, TextColor::Yellow);
		Print(" destroyed \n", TextColor::Red);
	}

	if (components.empty()) return;

	SetActive(false);

	for (Component* component : components)
	{
		if (component != nullptr)
		{
			component->OnDestroy();
			Destroy(*this, component);
		}
	}
}

bool GameObject::IsActive() const { return m_IsActive; }
void GameObject::SetActive(const bool& active)
{
	if (active == m_IsActive) return;

	m_IsActive = active;
	if (active == true)
	{
		for (const auto& component : components)
		{
			component->Awake();
			component->Start();
		}
	}
	else
	{
		for (const auto& component : components)
		{
			component->OnDisable();
		}
	}
}

void GameObject::Update(const float& deltaTime)
{
	if (!m_IsActive) return;

	for ( const auto component : components)
	{
		if (component->m_IsEnabled)
		{
			component->Update(deltaTime);
		}
	}
}