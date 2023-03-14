#pragma once
#include "Behavior.h"
#include "IDrawEvent.h"

class Actor : public Behavior, public IDrawEvent
{
private:
	int m_MaxHealth;
	int m_Health;

protected:
	Rigidbody2D* m_pRigidbody;

	Actor(const int& maxHealth);
	virtual void OnDeath() = 0;
	virtual void DrawMidground() const override = 0;
	virtual ~Actor() override = default;

public:
	int GetHealth() const { return m_Health; }
	virtual void OnDamage(const int& damage);
};
