#pragma once
#include "Behavior.h"

class Actor : public Behavior
{
public:
	int GetHealth() const { return m_Health; }
	virtual void OnDamage(const int& damage);

protected:
	Actor(const int& maxHealth);
	virtual void OnDeath() = 0;
	virtual ~Actor() override = default;

private:
	int m_MaxHealth;
	int m_Health;
};
