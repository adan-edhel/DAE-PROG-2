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

	State m_State{State::Falling};

	Rigidbody2D* m_RigidbodyPtr{};
	SpriteRenderer* m_RendererPtr{};
	Animator* m_Animator{};

	const Uint8* KBStatesPtr{nullptr};

	const float m_WalkSpeed{ 26 };
	const float m_JumpForce{ 5 };
	const int m_MaxJumps{2};
	int m_JumpsLeft{m_MaxJumps};

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

