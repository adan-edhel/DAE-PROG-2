#pragma once
#include "../Engine/Vector2.h"
#include "Component.h"
#include "IInputEvent.h"

class Rigidbody2D;

class InputActions final : public Component, public IInputEvent
{
public:
	InputActions();
	~InputActions() override = default;

protected:
	Vector2 m_MousePos{};

private:
	Rigidbody2D* m_pRigidbody{nullptr};

	const float walkSpeed{ 15 };
	const float jumpForce{ 5 };

	void OnKeyDown(const SDL_KeyboardEvent& e) override;
	void OnKeyUp(const SDL_KeyboardEvent& e) override;
	void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	void OnMouseUp(const SDL_MouseButtonEvent& e) override;
	void OnMouseMotion(const SDL_MouseMotionEvent& e) override;

	void Walk(const float& speed);
	void Jump(const float& force);
	void CutJump();
	void Attack();
};

