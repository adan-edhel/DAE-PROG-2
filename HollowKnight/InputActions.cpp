#include "pch.h"
#include "InputActions.h"

#include "Transform.h"
#include "GameObject.h"

#include "Rigidbody2D.h"
#include "SpriteLibrary.h"
#include "SpriteRenderer.h"

InputActions::InputActions() : Component("Input Actions")
{
}

void InputActions::Awake()
{
	if (m_pRigidbody == nullptr)
		m_pRigidbody = m_GameObject->GetComponent<Rigidbody2D>();

	m_SpriteRenderer = m_GameObject->GetComponent<SpriteRenderer>();
}

void InputActions::Update(const float& deltaTime)
{
	KBStatesPtr = SDL_GetKeyboardState(nullptr);

	if (KBStatesPtr[SDL_SCANCODE_A])
	{
		Walk(-walkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_D])
		{
			if (!m_SpriteRenderer->m_FlipX) m_SpriteRenderer->m_FlipX = true;
		}
	}
	if (KBStatesPtr[SDL_SCANCODE_D])
	{
		Walk(walkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_A])
		{
			if (m_SpriteRenderer->m_FlipX) m_SpriteRenderer->m_FlipX = false;
		}
	}
	if (KBStatesPtr[SDL_SCANCODE_LEFT] && KBStatesPtr[SDL_SCANCODE_UP])
	{
		Print("Left and up arrow keys are down\n");
	}
}

#pragma region Override
void InputActions::OnKeyDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:			// UP
		break;
	case SDLK_s:			// DOWN
		break;
	case SDLK_a:			// LEFT
		break;
	case SDLK_d:			// RIGHT
		break;
	case SDLK_SPACE:		// JUMP
		Jump(jumpForce);
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		m_SpriteRenderer->AssignSprite(SpriteLibrary::GetSprite(SpriteLibrary::Type::Knight));
		//m_GameObject->SetActive(!m_GameObject->Active());
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	}
}

void InputActions::OnKeyUp(const SDL_KeyboardEvent& e)
{

}

void InputActions::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	m_Transform->position = m_MousePos;
}

void InputActions::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	
}

void InputActions::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	m_MousePos = Vector2(static_cast<float>(e.x),
						 static_cast<float>(e.y));
}
#pragma endregion

#pragma region Actions
void InputActions::Walk(const float& speed)
{
	m_pRigidbody->AddForce(Vector2(speed, 0));
}

void InputActions::Jump(const float& force)
{
	if (m_pRigidbody->isGrounded())
	{
		m_pRigidbody->AddForce(Vector2(0, force));
	}
}

void InputActions::CutJump()
{
	
}

void InputActions::Attack()
{
	
}
#pragma endregion