#include "pch.h"
#include "Actor.h"
#include "Rigidbody2D.h"


Actor::Actor(const int& maxHealth, const std::string& sheetDirectory) : Behavior(),
	m_MaxHealth{ maxHealth },
	m_Sheet{ sheetDirectory }
{
	gameObject->transform->AddComponent(new Rigidbody2D());
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

void Actor::OnDeath()
{
	// Do death stuff
}

Actor::~Actor()
{

}