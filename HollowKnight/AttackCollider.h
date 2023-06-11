#pragma once
#include "Behavior.h"

class AttackCollider final : public Behavior
{
	bool m_EnemyHit{};

	void Awake() override;
	void OnDisable() override;
	void OnCollisionEnter(const Collision& collision) override;

	void PlaySound() const;
};
