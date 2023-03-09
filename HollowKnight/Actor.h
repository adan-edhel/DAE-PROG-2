#pragma once
#include "Behavior.h"
#include "Texture.h"

/**
 * \brief A base class for non-static objects within the game.
 */
class Actor : public AmrothFramework::Behavior
{
private:
	int m_MaxHealth;
	int m_Health;

public:
	int GetHealth() const { return m_Health; }
	virtual void OnDamage(const int& damage);

protected:
	Texture m_Sheet;

	Actor(const int& maxHealth, const std::string& sheetDirectory);
	virtual void OnDeath() = 0;
	virtual void Draw() const;
	virtual ~Actor() = default;
};

