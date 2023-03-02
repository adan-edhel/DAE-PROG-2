#include "pch.h"
#include "Actor.h"

Actor::Actor(const int& maxHealth, const std::string& sheetDirectory) :
	GameObject(),
	m_MaxHealth{ maxHealth },
	m_Sheet{ sheetDirectory }
{

}

void Actor::OnDamage(const int& damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		OnDeath();
	}
}

void Actor::Draw() const
{
	
}

void Actor::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Actor::OnDeath()
{
	// Do death stuff
}