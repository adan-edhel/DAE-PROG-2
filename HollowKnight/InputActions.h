#pragma once
#include "Component.h"
#include "IInputEvent.h"
#include "IUpdatable.h"

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
	Rigidbody2D* m_pRigidbody{nullptr};
	SpriteRenderer* m_SpriteRenderer{ nullptr };

	const Uint8* KBStatesPtr;

	const float walkSpeed{ 1 };
	const float jumpForce{ 5 };

	void Awake() override;
	void Update(const float& deltaTime) override;

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

