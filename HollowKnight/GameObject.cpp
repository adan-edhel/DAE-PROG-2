#include "pch.h"
#include "EventSystem.h"
#include "GameObject.h"

GameObject::GameObject()
{
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