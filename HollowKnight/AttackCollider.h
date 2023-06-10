#pragma once
#include "Behavior.h"

class AttackCollider final : public Behavior
{
	void OnCollisionEnter(const Collision& collision) override;
};
