#include "pch.h"
#include "Global.h"
#include "GameObject.h"

namespace AmrothFramework
{
	GameObject::GameObject()
	{
		Global::UpdateGameObjects.Connect(this, &GameObject::Update);
	}

	bool GameObject::isActive() const
	{
		return m_Active;
	}

	void GameObject::SetActive(const bool& active)
	{
		m_Active = active;
	}

	void GameObject::Update(const float& deltaTime)
	{
		if (!m_Active) return;
		transform.Update(deltaTime);
	}

	void GameObject::Draw() const
	{
	}

	GameObject::~GameObject()
	{
		Global::UpdateGameObjects.Disconnect(this, &GameObject::Update);
	}
}
