#pragma once
#include "Behavior.h"

class AudioSource;

class AttackCollider final : public Behavior
{
public:
	AttackCollider() = default;
	~AttackCollider() override = default;
	AttackCollider(const AttackCollider& other) = delete;
	AttackCollider(AttackCollider&& other) noexcept = delete;
	AttackCollider& operator=(const AttackCollider& other) = delete;
	AttackCollider& operator=(AttackCollider&& other) noexcept = delete;

private:
	AudioSource* m_AudioSource{};
	const float m_KnockbackForce{ 15 };
	bool m_EnemyHit{};

	void Awake() override;
	void OnDisable() override;
	void OnCollisionEnter(const Collision& collision) override;

	void PlaySound() const;
};
