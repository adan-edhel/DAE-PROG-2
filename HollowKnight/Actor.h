#pragma once
#include "AmrothStructs.h"
#include "Texture.h"

/**
 * \brief A base class for non-static objects within the game.
 */
class Actor
{
public:
	Actor(const int& maxHealth, const std::string& sheetDirectory);

	Transform m_Transform;

	// Getters
	int Health() const { return m_Health; }

	// Virtual functions
	virtual void OnDamage(const int& damage);
	virtual void Draw() const;

private:
	int m_MaxHealth;
	int m_Health{ m_MaxHealth };

protected:
	Texture m_Sheet;
	virtual void OnDeath();
};

