#pragma once
#include "Behavior.h"

class Collider;
class SpriteRenderer;

class Actor : public Behavior
{
public:
	Actor(const Actor& other) = delete;
	Actor(Actor&& other) noexcept = delete;
	Actor& operator=(const Actor& other) = delete;
	Actor& operator=(Actor&& other) noexcept = delete;

	// Returns actor health.
	int GetHealth() const { return m_Health; }
	// Heals actor.
	void Heal(const int& health);
	// Adds damage to actor.
	virtual void OnDamage();
	// Returns whether actor is alive.
	bool IsAlive() const;

protected:
	bool m_IsAlive{ true };
	const int m_MaxHealth;

	Actor(const int& maxHealth);
	~Actor() override = default;

	virtual void Awake() override;
	virtual void OnDeath() = 0;

private:
	int m_Health;
};