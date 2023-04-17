#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	inline static Vector2 s_PlayerPosition{};

	Enemy();
protected:
	~Enemy() override = default;
private:
	void OnDeath() override;
};
