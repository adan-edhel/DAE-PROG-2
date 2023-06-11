#pragma once
#include "Actor.h"
#include "SoundEffect.h"

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

	const float m_VelocityUpdateInterval{ 0.001f };
	float m_VelocityUpdateCounter{};
	Vector2 m_StoredVelocity{};

	SoundEffect m_Walking;
	SoundEffect m_LandingSoft;
	SoundEffect m_LandingHard;

	const Vector2 m_ColliderSize;
	const float m_SoftImpactThreshold{ 0.5 };
	const float m_HardImpactThreshold{ 7.0 };
	const float m_WalkSoundThreshold{ 0.5f };

	~Knight() override = default;
	void Start() override;
	void Update(const float& deltaTime) override;
	void HandleGroundImpact() const;
	void HandleWalkAudio() const;
	void OnDamage() override;
	void OnDeath() override;

	void OnCollisionEnter(const Collision& collision) override;
	void OnCollisionStay(const Collision& collision) override;
	void OnCollisionExit(const Collision& collision) override;
};
