#include "pch.h"
#include "InputActions.h"

#include <CORE.h>
#include <Transform.h>
#include <GameObject.h>

#include <SpriteRenderer.h>
#include <Rigidbody2D.h>
#include <Animator.h>
#include <Collider.h>

#include "AttackCollider.h"

InputActions::InputActions() :
m_State{State::Falling},
m_WalkSpeed{26},
m_JumpForce{5},
m_MaxJumps{2},
m_JumpsLeft{m_MaxJumps}
{
}

void InputActions::Start()
{
	m_RigidbodyPtr = m_GameObject->GetComponent<Rigidbody2D>();
	m_RendererPtr = m_GameObject->GetComponent<SpriteRenderer>();
	m_Animator = m_GameObject->GetComponent<Animator>();

	// Prepare collider
	const Collider* playerCollider{ m_GameObject->GetComponent<Collider>() };
	m_AttackCollider.AddComponent(new Collider())->SetSize(playerCollider->GetSize() + Vector2(50, 0));
	m_AttackCollider.AddComponent(new AttackCollider());
	m_ColliderOffset = playerCollider->GetSize().x + 50;
}

void InputActions::Update(const float& deltaTime)
{
	if (m_State != State::Attacking)
	{
		m_AttackOffsetMult = float(m_RendererPtr->m_FlipX ? -1 : 1);
	}

	m_AttackCollider.m_Transform->position = 
		Vector2(m_Transform->position.x + (m_ColliderOffset * m_AttackOffsetMult), m_Transform->position.y);

	OnKey(deltaTime);

	AnimationConditions(deltaTime);
	UpdateAnimation();

	// debug movement
	if (m_RigidbodyPtr->m_IsStatic)
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
void InputActions::OnKey(const float& deltaTime)
{
	KBStatesPtr = SDL_GetKeyboardState(nullptr);

	if (m_RigidbodyPtr->isGrounded()) m_JumpsLeft = m_MaxJumps;

	// return if in hurt state
	if (m_State == State::Hurt) return;

	if (KBStatesPtr[SDL_SCANCODE_LEFT])
	{
		Walk(-m_WalkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_RIGHT])
		{
			if (!m_RendererPtr->m_FlipX)
			{
				m_RendererPtr->m_FlipX = true;
			}
		}
	}
	if (KBStatesPtr[SDL_SCANCODE_RIGHT])
	{
		Walk(m_WalkSpeed * deltaTime);
		if (!KBStatesPtr[SDL_SCANCODE_LEFT])
		{
			if (m_RendererPtr->m_FlipX)
			{
				m_RendererPtr->m_FlipX = false;
			}
		}
	}
}

void InputActions::OnKeyDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:			// JUMP
		m_JumpsLeft--;
		if(m_JumpsLeft > 0)
		{
			Jump();
			m_State = State::Jumping;
		}
		break;
	case SDLK_x:			// ATTACK
		Attack();
		break;
	case SDLK_c:			// DASH
		break;
	case SDLK_a:			// FOCUS / CAST
		break;
	case SDLK_s:			// Super Dash
		break;
	case SDLK_d:			// DREAM NAIL
		break;
	case SDLK_f:			// Quick Cast
		break;
	case SDLK_i:			// Inventory
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
	case SDLK_F5:			// Clear Console
		ClearConsole();
		break;
	}
}

void InputActions::OnKeyUp(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:		// CUT JUMP
		CutJump();
		break;
	}
}

void InputActions::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	if (CORE::s_DebugMode)
	{
		//m_Transform->position = m_MousePos;
		//Print(m_Transform->position.ToString() + "\n");
	}
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

void InputActions::Attack()
{
	if (m_State == State::Attacking) return;

	// Save state
	m_StoredState = m_State;

	m_State = State::Attacking;
	m_AttackCountdown = m_AttackDuration;
}

void InputActions::AnimationConditions(const float& deltaTime)
{
	// Local fields
	const float walkCheckThreshold{ 0.5f };
	const float fallCheckThreshold{ -0.5f };

	// Update fields
	m_AttackCountdown -= deltaTime;

	// Automatic conditions
	const bool walking{ std::abs(m_RigidbodyPtr->GetVelocity().x) >= walkCheckThreshold };
	m_AttackCollider.SetActive(m_State == State::Attacking ? true : false);

	switch (m_State)
	{
	case State::Attacking:
		if (m_AttackCountdown > 0)
			return;
		else
			m_State = m_StoredState;
		break;
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

	// Fall condition
	if (!m_RigidbodyPtr->isGrounded() && m_RigidbodyPtr->GetVelocity().y < fallCheckThreshold)
	{
		m_State = State::Falling;
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