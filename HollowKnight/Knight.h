#pragma once
#include "Actor.h"

class Animator;

class Knight final : public Actor
{
public:
	Knight();
	Knight(const Knight& other) = default;
	Knight& operator=(const Knight& other) = default;

private:
	Animator* m_AnimatorPtr;
	const Vector2 m_ColliderSize;

	~Knight() override = default;
	void Start() override;
	void OnDeath() override;
	void OnCollisionEnter(const Collision& collision) override;
	void OnCollisionStay(const Collision& collision) override;
	void OnCollisionExit(const Collision& collision) override;
};
