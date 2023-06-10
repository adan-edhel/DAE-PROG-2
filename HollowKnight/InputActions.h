#pragma once
#include "Component.h"
#include "IUpdatable.h"
#include "IInputEvent.h"

#include <GameObject.h>

class Animator;
class SpriteRenderer;
class Rigidbody2D;

class InputActions final : public Component, IInputEvent, IUpdatable
{
public:
	InputActions();

protected:
	Vector2 m_MousePos{};

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

	const Uint8* KBStatesPtr{};

	// Movement fields
	const float m_JumpResetThreshold{ -1.0f };
	const float m_WalkSpeed;
	const float m_JumpForce;
	const int m_MaxJumps;
	int m_JumpsLeft;

	// Attack fields
	GameObject m_AttackCollider{"Attack Collider"};
	float m_ColliderOffset{};
	float m_AttackCountdown{};
	float m_AttackOffsetMult{};

	// Functions
	void Start() override;
	void Update(const float& deltaTime) override;

	void OnKey(const float& deltaTime);
	void OnKeyDown(const SDL_KeyboardEvent& e) override;
	void OnKeyUp(const SDL_KeyboardEvent& e) override;
	void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	void OnMouseUp(const SDL_MouseButtonEvent& e) override;
	void OnMouseMotion(const SDL_MouseMotionEvent& e) override;

	void Walk(const float& speed) const;
	void Jump() const;
	void CutJump() const;
	void Attack();

	void AnimationConditions(const float& deltaTime);
	void UpdateAnimation() const;
};

