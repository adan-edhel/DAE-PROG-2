#include "pch.h"
#include "Actor.h"
#include "EventSystem.h"
#include "Rigidbody2D.h"

Actor::Actor(const int& maxHealth) :
	Behavior(),
	m_MaxHealth{ maxHealth },
	m_Health{m_MaxHealth}
{
	m_pRigidbody = dynamic_cast<Rigidbody2D*>(AddComponent(new Rigidbody2D()));
}

void Actor::OnDamage(const int& damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		OnDeath();
	}
}