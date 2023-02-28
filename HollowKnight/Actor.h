#pragma once
#include "Texture.h"
#include "Vector2.h"

struct Transform
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
};

/**
 * \brief A base class for non-static objects within the game.
 */
class Actor
{
public:
	Actor(const int& maxHealth, const std::string& sheetDirectory);

	Transform transform() const { return m_Transform; }
	int Health() const { return m_Health; }

	virtual void OnDamage(const int& damage);
	virtual void Draw() const;

private:
	Transform m_Transform;
	int m_MaxHealth;
	int m_Health{ m_MaxHealth };

protected:
	Texture m_Sheet;
	virtual void OnDeath();
};

