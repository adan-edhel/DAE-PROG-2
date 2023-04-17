#pragma once
#include "Actor.h"

class Animator;

class Knight final : public Actor
{
public:
	Knight();

private:
	Animator* m_AnimatorPtr;

	const Vector2 colliderSize{ 40, 70 };

	~Knight() override = default;
	void Awake() override;
	void OnDeath() override;
};
