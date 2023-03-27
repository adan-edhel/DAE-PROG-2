#pragma once
#include "Actor.h"

class Knight final : public Actor
{
public:
	Knight();

private:
	~Knight() override = default;

	void OnDeath() override;

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

