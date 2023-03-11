#include "pch.h"
#include "DelegateRegistry.h"
#include "GameObject.h"

namespace AmrothFramework
{
	GameObject::GameObject()
	{
		DelegateRegistry::regularUpdate.Connect(this, &GameObject::Update);
	}

	bool GameObject::isActive() const
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
	}

	void GameObject::Draw() const
	{
	}

	GameObject::~GameObject()
	{
		DelegateRegistry::regularUpdate.Disconnect(this, &GameObject::Update);
	}
}
