#pragma once
#include "Behavior.h"

class AudioSource;

class AttackCollider final : public Behavior
{
	AudioSource* m_AudioSource{};
	bool m_EnemyHit{};

	void Awake() override;
	void OnDisable() override;
	void OnCollisionEnter(const Collision& collision) override;

	void PlaySound() const;
};
