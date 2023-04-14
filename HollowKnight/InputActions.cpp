#include "pch.h"
#include "InputActions.h"

#include "Transform.h"
#include "GameObject.h"
#include "GameSettings.h"

#include "Rigidbody2D.h"
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

	if (GameSettings::s_DebugMode)
	{
		if (KBStatesPtr[SDL_SCANCODE_UP])
		{
			m_Transform->position.y += walkSpeed / 3;
			m_pRigidbody->m_Velocity = Vector2{};
		}

		if (KBStatesPtr[SDL_SCANCODE_DOWN])
		{
			m_Transform->position.y -= walkSpeed / 3;
			m_pRigidbody->m_Velocity = Vector2{};
		}

		if (KBStatesPtr[SDL_SCANCODE_LEFT])
		{
			m_Transform->position.x -= walkSpeed / 3;
			m_pRigidbody->m_Velocity = Vector2{};
		}

		if (KBStatesPtr[SDL_SCANCODE_RIGHT])
		{
			m_Transform->position.x += walkSpeed / 3;
			m_pRigidbody->m_Velocity = Vector2{};
		}
	}
}

#pragma region Override
void InputActions::OnKeyDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:		// JUMP
		Jump(jumpForce);
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	case SDLK_F1:			// TOGGLE DEBUG
		GameSettings::s_DebugMode = !GameSettings::s_DebugMode;
		s_Debug = !s_Debug;
	case SDLK_F2:
		Print(m_Transform->position.ToString() + "\n");
		m_pRigidbody->m_IsStatic = !m_pRigidbody->m_IsStatic;
		m_pRigidbody->m_Velocity = Vector2{};
		break;
	}
}

void InputActions::OnKeyUp(const SDL_KeyboardEvent& e)
{

}

void InputActions::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	m_Transform->position = m_MousePos;
	Print(m_Transform->position.ToString() + "\n");
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
	m_pRigidbody->AddForce(Vector2(0, force));
}

void InputActions::CutJump()
{
	
}

void InputActions::Attack()
{
	
}
#pragma endregion