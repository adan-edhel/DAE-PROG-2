#pragma once
#include "InputActions.h"
#include "Actor.h"

class Knight final : public Actor, public InputActions
{
public:
	Knight();
	~Knight() override = default;

private:
	SpriteRenderer* m_pSpriteRenderer;

	void Update(const float& deltaTime);
	void DrawMidground() const override;
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

