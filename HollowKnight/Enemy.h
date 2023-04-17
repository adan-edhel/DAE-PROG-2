#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	inline static Vector2 s_PlayerPosition{};

	Enemy();
	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;

protected:
	~Enemy() override = default;

private:
	void OnDeath() override;
};
