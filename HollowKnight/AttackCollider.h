#pragma once
#include "Behavior.h"

class AttackCollider : public Behavior
{
	void OnCollisionEnter(const Collision& collision) override;
};
