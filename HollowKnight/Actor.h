#pragma once
#include "GameObject.h"
#include "Texture.h"

/**
 * \brief A base class for non-static objects within the game.
 */
class Actor : public GameObject
{
public:
	Actor(const int& maxHealth, const std::string& sheetDirectory);

	// Getters
	int Health() const { return m_Health; }

	// Virtual functions
	virtual void OnDamage(const int& damage);
	virtual void Draw() const;

	GameObject* gameObject{ GetReference() };

private:
	int m_MaxHealth;
	int m_Health{ m_MaxHealth };

protected:
	Texture m_Sheet;
	virtual void OnDeath();
	virtual void Update(float deltaTime) override;
};

