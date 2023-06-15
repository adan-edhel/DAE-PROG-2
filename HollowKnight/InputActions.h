#pragma once
#include "Component.h"
#include "IUpdatable.h"
#include "IInputEvent.h"

#include <GameObject.h>

class Knight;
class Animator;
class AudioSource;
class SpriteRenderer;
class Rigidbody2D;

class InputActions final : public Component, IInputEvent, IUpdatable
{
public:
	InputActions();

private:
	enum class State
	{
		Idle,
		Walking,
		Jumping,
		Falling,
		Hurt,
		Attacking
	};

	State m_State;
	State m_StoredState;

	Rigidbody2D* m_RigidbodyPtr{};
	SpriteRenderer* m_RendererPtr{};
	AudioSource* m_AudioSource{};

	const Uint8* KBStatesPtr{};
	Vector2 m_MousePos{};

	// Healing
	const int m_ShardsToHeal{ 4 };

	// Movement fields
	const float m_JumpResetThreshold;
;	const float m_WalkSpeed;
	const float m_JumpForce;
	const int m_MaxJumps;
	int m_JumpsLeft;

	// Dash fields
	const float m_DashVelocity;
	const float m_DashCooldown;
	float m_DashCountdown{};

	// Attack fields
	GameObject m_AttackCollider{"Attack Collider"};
	float m_ColliderOffset{};
	float m_AttackCountdown{};
	float m_AttackOffsetMult{};

	// Base Functions
	void Start() override;
	void Update(const float& deltaTime) override;

	// Input Functions
	void OnKey(const float& deltaTime);
	void OnKeyDown(const SDL_KeyboardEvent& e) override;
	void OnKeyUp(const SDL_KeyboardEvent& e) override;
	void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	void OnMouseMotion(const SDL_MouseMotionEvent& e) override;

	// Action Functions
	void Walk(const float& speed) const;
	void Jump() const;
	void CutJump() const;
	void Dash() const;
	void Heal() const;
	void Attack();

	// Animation Functions
	void HandleConditions(const float& deltaTime);
	void UpdateAnimation() const;

	// Helper Functions
	[[nodiscard]] bool CanJump() const { return m_JumpsLeft > 0; }
	[[nodiscard]] bool CanDash() const { return m_DashCountdown >= m_DashCooldown; }
};

