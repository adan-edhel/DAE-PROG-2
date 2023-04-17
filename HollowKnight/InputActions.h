#pragma once
#include "Component.h"
#include "IInputEvent.h"
#include "IUpdatable.h"

class Animator;
class SpriteRenderer;
class Rigidbody2D;

class InputActions final : public Component, public IInputEvent, public IUpdatable
{
public:
	InputActions();
	InputActions(const InputActions& other) = default;
	InputActions& operator=(const InputActions& other) = default;
	~InputActions() override = default;

protected:
	Vector2 m_MousePos{};

private:
	enum class State
	{
		Idle,
		Walking,
		Jumping,
		Falling,
		Attacking
	};

	State m_State;

	Rigidbody2D* m_RigidbodyPtr{};
	SpriteRenderer* m_RendererPtr{};
	Animator* m_Animator{};

	const Uint8* KBStatesPtr{};

	const float m_WalkSpeed;
	const float m_JumpForce;
	const int m_MaxJumps;
	int m_JumpsLeft;

	void Start() override;
	void Update(const float& deltaTime) override;

	void OnKeyDown(const SDL_KeyboardEvent& e) override;
	void OnKeyUp(const SDL_KeyboardEvent& e) override;
	void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	void OnMouseUp(const SDL_MouseButtonEvent& e) override;
	void OnMouseMotion(const SDL_MouseMotionEvent& e) override;

	void Walk(const float& speed) const;
	void Jump() const;
	void CutJump() const;
	void Attack() const;

	void AnimationConditions();
	void UpdateAnimation() const;
};

