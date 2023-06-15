#pragma once
#include "Actor.h"

class AudioSource;
class Rigidbody2D;
class Animator;

class Knight final : public Actor
{
public:
	inline static Knight* m_Instance{};

	Knight();
	~Knight() override;
	Knight(const Knight& other) = default;
	Knight& operator=(const Knight& other) = default;

private:
	// Component pointers
	Rigidbody2D* m_RigidbodyPtr;
	AudioSource* m_FootStepSource{};
	AudioSource* m_AudioSource{};

	const float m_VelocityUpdateInterval{ 0.001f };
	float m_VelocityUpdateCounter{};
	Vector2 m_StoredVelocity{};

	const Vector2 m_ColliderSize;
	const float m_KnockbackForce{ 15 };
	const float m_SoftImpactThreshold{ 0.5 };
	const float m_HardImpactThreshold{ 7.0 };
	const float m_WalkSoundThreshold{ 0.5f };

	void Start() override;
	void Update(const float& deltaTime) override;
	void HandleGroundImpact() const;
	void HandleWalkAudio() const;
	void OnDamage() override;
	void OnDeath() override;

	void OnCollisionEnter(const Collision& collision) override;
};
