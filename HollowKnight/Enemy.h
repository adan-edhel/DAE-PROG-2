#pragma once
#include "Actor.h"

class Animator;
class Rigidbody2D;

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override = default;
	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;

protected:
	enum class Direction
	{
		Left,
		Right
	};
	Direction m_Direction{Direction::Left};

	Animator* m_AnimatorPtr;
	Rigidbody2D* m_RigidbodyPtr;
	SpriteRenderer* m_SpriteRendererPtr;

	const int m_ShardDrops{ 2 };
	const Vector2 m_ColliderSize{ 110, 80 };
	const float m_BaseTurnInterval{ 5 };
	const float m_TurnIntervalOffset{ 3 };
	float m_TurnCounter{};

	void Awake() override;
	void Update(const float& deltaTime) override;
	void OnDeath() override;

	virtual void HandleStates(const float& deltaTime) = 0;
	virtual void HandleAnimation() const = 0;
};