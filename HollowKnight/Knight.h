#pragma once
#include "Actor.h"

class Knight final : public Actor
{
public:
	Knight();

private:
	const Vector2 colliderSize{ 40, 70 };

	~Knight() override = default;
	void Awake() override;
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

