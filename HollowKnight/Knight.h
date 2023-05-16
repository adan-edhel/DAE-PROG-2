#pragma once
#include "Actor.h"

class Rigidbody2D;
class Animator;

class Knight final : public Actor
{
public:
	Knight();
	Knight(const Knight& other) = default;
	Knight& operator=(const Knight& other) = default;

private:
	// Component pointers
	Rigidbody2D* m_RigidbodyPtr;

	const Vector2 m_ColliderSize;
	const float m_ImpactThreshold{ 7.0 };

	~Knight() override = default;
	void Start() override;
	void Update(const float& deltaTime) override;
	void OnDeath() override;

	void OnCollisionEnter(const Collision& collision) override;
	void OnCollisionStay(const Collision& collision) override;
	void OnCollisionExit(const Collision& collision) override;
};
