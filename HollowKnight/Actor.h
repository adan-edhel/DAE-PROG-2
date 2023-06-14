#pragma once
#include "Behavior.h"

class Collider;
class SpriteRenderer;

class Actor : public Behavior
{
public:
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;

	int GetHealth() const { return m_Health; }
	virtual void OnDamage();
	bool IsAlive() const;

protected:
	bool m_IsAlive{ true };
	const int m_MaxHealth;

	Actor(const int& maxHealth);
	virtual ~Actor() override = default;

	virtual void Awake() override;
	virtual void OnDeath() = 0;

private:
	int m_Health;
};