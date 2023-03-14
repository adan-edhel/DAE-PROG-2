#pragma once
#include "IEvent.h"
#include "Vector2.h"

class GameObject;
class Rigidbody2D;

class InputActions : public IEvent
{
protected:
	Vector2 m_MousePos{};

	InputActions(GameObject& player);
	virtual ~InputActions() override = default;

private:
	GameObject* m_pGameObject;
	Rigidbody2D* m_pRigidbody;

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

