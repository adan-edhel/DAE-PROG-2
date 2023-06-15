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
		Turning
	};

public:
	Crawlid();
	~Crawlid() override = default;
	Crawlid(const Crawlid& other) = delete;
	Crawlid(Crawlid&& other) noexcept = delete;
	Crawlid& operator=(const Crawlid& other) = delete;
	Crawlid& operator=(Crawlid&& other) noexcept = delete;

private:
	State m_State{State::Walking};
	AudioSource* m_AudioSourcePtr;
	SoundEffect m_FootSteps;

	const float m_MoveSpeed{20};

	void Start() override;
	void Update(const float& deltaTime) override;
	void OnDeath() override;

	void Walk(const float& deltaTime) const;
	void Turn(const float& deltaTime);

	void HandleStates(const float& deltaTime) override;
	void HandleAnimation() const override;
};
