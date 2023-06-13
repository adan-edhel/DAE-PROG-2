#pragma once
#include "Enemy.h"
#include "SoundEffect.h"

class AudioSource;
class Rigidbody2D;
class Animator;

class Crawlid final : public Enemy
{
	enum class State
	{
		Walking,
		Turning,
		Dying
	};

	enum class Direction
	{
		Left,
		Right
	};

public:
	Crawlid();
	~Crawlid() override = default;
	Crawlid(const Crawlid& other) = delete;
	Crawlid& operator=(const Crawlid& other) = delete;

private:
	Animator* m_AnimatorPtr;
	Rigidbody2D* m_Rigidbody;
	SpriteRenderer* m_SpriteRend;
	AudioSource* m_AudioSource;

	State m_State;
	Direction m_Direction;

	SoundEffect m_FootSteps;

	const Vector2 m_ColliderSize;
	const float m_WalkSpeed;
	const float m_TurnInterval;
	float m_TurnCounter{};

	void Start() override;
	void Update(const float& deltaTime) override;
	void OnDeath() override;

	void Walk(const float& deltaTime) const;
	void Turn(const float& deltaTime);
	void ManageStates(const float& deltaTime);
	void UpdateAnimation() const;
};
