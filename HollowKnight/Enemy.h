#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;

protected:
	Enemy();
	~Enemy() override = default;

	void Awake() override;
	void OnDeath() override;
};
