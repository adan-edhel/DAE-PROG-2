#pragma once
#include "Behavior.h"
#include "Texture.h"

/**
 * \brief A base class for non-static objects within the game.
 */
class Actor : public AmrothFramework::Behavior
{
public:
	Actor(const int& maxHealth, const std::string& sheetDirectory);
	~Actor();

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

