#pragma once
#include "Actor.h"

/**
 * \brief A class for the titular character of the game.
 */
class Knight final : public Actor
{
public:
	Knight();
	void Draw() const override;
	void Update(const float& deltaTime);
	void OnDeath() override;
	~Knight() override = default;

private:

	enum class AnimState
	{
		Idle,
		Walking,
		Attacking,
		Jumping,
		Hurt,
		Dying
	};

	AnimState m_AnimState{ AnimState::Idle };
};

