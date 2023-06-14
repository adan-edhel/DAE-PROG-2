#pragma once
#include "Enemy.h"
#include "SoundEffect.h"

class Animator;
class Rigidbody2D;
class AudioSource;

class Vengefly final : public Enemy
{
	enum class State
	{
		Flying,
		Turning,
		Startled,
		Charging
	};

public:
	Vengefly();
	~Vengefly() override;
	Vengefly(const Vengefly& other) = delete;
	Vengefly& operator=(const Vengefly& other) = delete;

private:
	std::vector<SoundEffect*> m_StartleSounds;
	AudioSource* m_StartleSourcePtr;
	AudioSource* m_FlySourcePtr;
	SoundEffect m_WingSounds;

	State m_State{State::Flying};

	const float m_AttackDistance{300};
	const float m_AttackSpeed{200};
	const float m_MoveSpeed{20};
	bool m_Hostile{ false };

	void Start() override;
	void Update(const float& deltaTime) override;
	void OnDamage() override;
	void OnDeath() override;

	void Fly(const float& deltaTime) const;
	void Turn(const float& deltaTime);
	bool PlayerInAttackRange() const;
	bool PlayerOnLeft() const;
	SoundEffect* GetRandomStartleSound() const;

	void HandleStates(const float& deltaTime) override;
	void HandleAnimation() const override;
};