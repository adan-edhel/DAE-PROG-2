#pragma once
#include "Behavior.h"

class Collider;
class SpriteRenderer;

class Actor : public Behavior
{
public:
	int GetHealth() const { return m_Health; }
	virtual void OnDamage(const int& damage);

protected:
	Actor(const int& maxHealth);
	virtual ~Actor() override = default;

	virtual void Awake() override;
	virtual void OnDeath() = 0;

private:
	int m_MaxHealth;
	int m_Health;
};