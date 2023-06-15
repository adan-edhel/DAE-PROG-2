#include "GameObject.h"

#include "AmrothUtils.h"
#include "CORE.h"
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
	if (CORE::s_DebugMode)
	{
		if (!m_Name.empty())
		{
			Print("(x) ", TextColor::Red);
			Print(m_Name, TextColor::Yellow);
			Print(" destroyed \n", TextColor::Red);
		}
	}

	SetActive(false);

	if (!components.empty())
	{
		for (Component* component : components)
		{
			if (component != nullptr)
			{
				component->OnDestroy();
				Destroy(*this, component);
			}
		}
	}
}

bool GameObject::IsActive() const { return m_IsActive; }
void GameObject::SetActive(const bool& active)
{
	if (active == m_IsActive) return;

	m_IsActive = active;

	if (!components.empty())
	{
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
}

void GameObject::Update(const float& deltaTime)
{
	if (!m_IsActive) return;

	if (!components.empty())
	{
		for (const auto component : components)
		{
			if (component->m_IsEnabled)
			{
				component->Update(deltaTime);
			}
		}
	}
}