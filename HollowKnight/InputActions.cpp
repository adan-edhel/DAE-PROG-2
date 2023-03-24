#include "pch.h"

#include "Transform.h"
#include "GameObject.h"
#include "Rigidbody2D.h"
#include "InputActions.h"

#include "SpriteLibrary.h"
#include "SpriteRenderer.h"

InputActions::InputActions() : Component("Input Actions")
{
}

#pragma region Override
void InputActions::OnKeyDown(const SDL_KeyboardEvent& e)
{
	if (m_pRigidbody == nullptr) 
		m_pRigidbody = m_GameObject->GetComponent<Rigidbody2D>();

	switch (e.keysym.sym)
	{
	case SDLK_w:			// UP
		break;
	case SDLK_s:			// DOWN
		break;
	case SDLK_a:			// LEFT
		Walk(-walkSpeed);
		break;
	case SDLK_d:			// RIGHT
		Walk(walkSpeed);
		break;
	case SDLK_SPACE:		// JUMP
		Jump(jumpForce);
		m_GameObject->GetComponent<SpriteRenderer>()->m_SpritePtr = SpriteLibrary::GetSprite(SpriteLibrary::Type::Knight);
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		m_GameObject->SetActive(!m_GameObject->Active());
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	default:
		break;
	}
}

void InputActions::OnKeyUp(const SDL_KeyboardEvent& e)
{
	if (m_pRigidbody == nullptr)
		m_pRigidbody = m_GameObject->GetComponent<Rigidbody2D>();
}

void InputActions::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	if (m_GameObject != nullptr)
		m_GameObject->m_Transform->position = m_MousePos;
}

void InputActions::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	
}

void InputActions::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	m_MousePos = Vector2(e.x, e.y);
}
#pragma endregion

#pragma region Actions
void InputActions::Walk(const float& speed)
{
	m_pRigidbody->AddForce(Vector2(speed, 0));
}

void InputActions::Jump(const float& force)
{
	m_pRigidbody->AddForce(Vector2(0, force));
}

void InputActions::CutJump()
{
	
}

void InputActions::Attack()
{
	
}
#pragma endregion