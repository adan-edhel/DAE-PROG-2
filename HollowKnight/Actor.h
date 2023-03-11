#pragma once
#include "Behavior.h"

using AmrothFramework::SpriteRenderer;
using AmrothFramework::Rigidbody2D;
using AmrothFramework::Behavior;
using AmrothFramework::Animator;

class Actor : public Behavior
{
private:
	int m_MaxHealth;
	int m_Health;

protected:
	Rigidbody2D* m_Rigidbody;

	Actor(const int& maxHealth);
	virtual void OnDeath() = 0;
	virtual void Draw() const = 0;
	virtual ~Actor() = default;

public:
	int GetHealth() const { return m_Health; }
	virtual void OnDamage(const int& damage);
};