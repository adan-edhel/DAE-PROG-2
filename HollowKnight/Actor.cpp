#include "pch.h"
#include "Actor.h"

#include "Animator.h"
#include "Collider.h"
#include "Rigidbody2D.h"
#include "SpriteRenderer.h"

Actor::Actor(const int& maxHealth) :
	m_MaxHealth{ maxHealth },
	m_Health{m_MaxHealth}
{
}

void Actor::Awake()
{
	m_GameObject->AddComponent(new SpriteRenderer(nullptr, 12, 12));
	m_GameObject->AddComponent(new Collider());
	m_GameObject->AddComponent(new Animator());
	m_GameObject->AddComponent(new Rigidbody2D());
}

void Actor::OnDamage(const int& damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		OnDeath();
	}
}