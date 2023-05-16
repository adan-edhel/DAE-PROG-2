#include "pch.h"
#include "Actor.h"

#include "Camera.h"
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
	SpriteRenderer* renderer = m_GameObject->AddComponent(new SpriteRenderer());
	m_GameObject->AddComponent(new Collider());
	m_GameObject->AddComponent(new Animator());
	m_GameObject->AddComponent(new Rigidbody2D());

	renderer->SetLayer(int(IDrawable::Layers::Actors));
}

void Actor::OnDamage()
{
	if (m_Health <= 0) return;

	m_Health--;
	Print(m_GameObject->m_Name + " is damaged! ");
	Print("New health: " + std::to_string(m_Health) + "\n");
	Camera::m_MainPtr->SetShake();

	if (m_Health <= 0)
	{
		OnDeath();
	}
}