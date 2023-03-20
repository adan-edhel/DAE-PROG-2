#include "pch.h"
#include "Actor.h"

Actor::Actor(const int& maxHealth) :
	m_MaxHealth{ maxHealth },
	m_Health{m_MaxHealth}
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