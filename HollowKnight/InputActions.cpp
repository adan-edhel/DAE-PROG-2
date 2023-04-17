#include "pch.h"
#include "InputActions.h"

#include <CORE.h>
#include <Transform.h>
#include <GameObject.h>

#include <SpriteRenderer.h>
#include <Rigidbody2D.h>
#include <Animator.h>

InputActions::InputActions() : Component("Input Actions")
{
}

void InputActions::Start()
{
	m_RigidbodyPtr = m_GameObject->GetComponent<Rigidbody2D>();
	m_RendererPtr = m_GameObject->GetComponent<SpriteRenderer>();
	m_Animator = m_GameObject->GetComponent<Animator>();
}

void InputActions::Update(const float& deltaTime)
{
	KBStatesPtr = SDL_GetKeyboardState(nullptr);

	if (m_RigidbodyPtr->isGrounded()) m_JumpsLeft = m_MaxJumps;

	if (KBStatesPtr[SDL_SCANCODE_A])
	{
		Walk(-m_WalkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_D])
		{
			if (!m_RendererPtr->m_FlipX) m_RendererPtr->m_FlipX = true;
		}
	}
	if (KBStatesPtr[SDL_SCANCODE_D])
	{
		Walk(m_WalkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_A])
		{
			if (m_RendererPtr->m_FlipX) m_RendererPtr->m_FlipX = false;
		}
	}

	AnimationConditions();
	UpdateAnimation();

	if (CORE::s_DebugMode)
	{
		if (KBStatesPtr[SDL_SCANCODE_UP])
		{
			m_Transform->position.y += m_WalkSpeed / 3;
			m_RigidbodyPtr->SetVelocity(0,0);
		}

		if (KBStatesPtr[SDL_SCANCODE_DOWN])
		{
			m_Transform->position.y -= m_WalkSpeed / 3;
			m_RigidbodyPtr->SetVelocity(0, 0);
		}

		if (KBStatesPtr[SDL_SCANCODE_LEFT])
		{
			m_Transform->position.x -= m_WalkSpeed / 3;
			m_RigidbodyPtr->SetVelocity(0, 0);
		}

		if (KBStatesPtr[SDL_SCANCODE_RIGHT])
		{
			m_Transform->position.x += m_WalkSpeed / 3;
			m_RigidbodyPtr->SetVelocity(0, 0);
		}
	}
}

#pragma region Override
void InputActions::OnKeyDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:		// JUMP
		m_JumpsLeft--;
		if(m_JumpsLeft > 0)
		{
			Jump();
			m_State = State::Jumping;
		}
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
		CORE::s_DebugMode = !CORE::s_DebugMode;
	case SDLK_F2:			// PRINT PLAYER POSITION
		Print(m_Transform->position.ToString() + "\n");
		break;
	case SDLK_F3:			// TOGGLE STATIC PLAYER
		m_RigidbodyPtr->m_IsStatic = !m_RigidbodyPtr->m_IsStatic;
		m_RigidbodyPtr->SetVelocity(0, 0);
		break;
	}
}

void InputActions::OnKeyUp(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:		// CUT JUMP
		CutJump();
		break;
	}
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
void InputActions::Walk(const float& speed) const
{
	m_RigidbodyPtr->AddForce(Vector2(speed, 0));
}

void InputActions::Jump() const
{
	m_RigidbodyPtr->AddForce(Vector2(0, m_JumpForce));
}

void InputActions::CutJump() const
{
	if (!m_RigidbodyPtr->isGrounded() && m_RigidbodyPtr->GetVelocity().y > 0.5f)
	{
		m_RigidbodyPtr->AddForce(Vector2(0, -m_JumpForce / 3));
	}
}

void InputActions::Attack() const
{
	
}

void InputActions::AnimationConditions()
{
	const float walkCheckThreshold{ 0.5f };
	const float fallCheckThreshold{ -0.5f };
	const bool walking{ std::abs(m_RigidbodyPtr->GetVelocity().x) >= walkCheckThreshold };

	// Fall condition
	if (!m_RigidbodyPtr->isGrounded() && m_RigidbodyPtr->GetVelocity().y < fallCheckThreshold)
	{
		m_State = State::Falling;
	}

	switch (m_State)
	{
	case State::Idle:
		if (walking && m_RigidbodyPtr->isGrounded()) m_State = State::Walking;
		break;
	case State::Walking:
		if (!walking && m_RigidbodyPtr->isGrounded()) m_State = State::Idle;
		break;
	case State::Falling:
		if (m_RigidbodyPtr->isGrounded())
		{
			if (walking) m_State = State::Walking;
			else  m_State = State::Idle;
		}
		break;
	}
}

void InputActions::UpdateAnimation() const
{
	std::string name{};

	switch (m_State)
	{
	case State::Idle:
		name = "Idle";
		break;
	case State::Walking:
		name = "Walk";
		break;
	case State::Jumping:
		name = "Jump";
		break;
	case State::Falling:
		name = "Fall";
		break;
	case State::Attacking:
		name = "Attack1";
		break;
	}

	if (!name.empty()) m_Animator->Play(name);
}
#pragma endregion