#include "pch.h"
#include "InputActions.h"

// Component
#include <CORE.h>
#include <Transform.h>
#include <Rigidbody2D.h>
#include <GameObject.h>
#include <Animator.h>
#include <Collider.h>
#include <Animation.h>
#include <AudioSource.h>
#include <SpriteRenderer.h>

#include "AnimLibrary.h"
#include "AttackCollider.h"
#include "AudioLibrary.h"
#include "Knight.h"

InputActions::InputActions() :
	m_State{ State::Falling },
	m_JumpResetThreshold{ 1.0f },
	m_WalkSpeed{ 26 },
	m_JumpForce{ 6 },
	m_MaxJumps{ 1 },
	m_JumpsLeft{},
	m_DashVelocity{ 50 },
	m_DashCooldown{ 5 }
{
}

void InputActions::Start()
{
	if (m_AudioSource == nullptr)
	{
		m_AudioSource = m_GameObject->AddComponent(new AudioSource(false, false));
	}
	m_RigidbodyPtr = m_GameObject->GetComponent<Rigidbody2D>();
	m_RendererPtr = m_GameObject->GetComponent<SpriteRenderer>();

	// Prepare collider
	const Collider* playerCollider{ m_GameObject->GetComponent<Collider>() };
	m_AttackCollider.AddComponent(new Collider())->SetSize(playerCollider->GetSize());
	m_AttackCollider.AddComponent(new AttackCollider());
	m_ColliderOffset = playerCollider->GetSize().x;
}

void InputActions::Update(const float& deltaTime)
{
	// Update Attack Direction
	if (m_State != State::Attacking)
	{
		m_AttackOffsetMult = float(m_RendererPtr->m_FlipX ? -1 : 1);
	}
	// Update Attack Position
	const Vector2 offset{ m_Transform->position.x + (m_ColliderOffset * m_AttackOffsetMult),
							m_Transform->position.y };
	m_AttackCollider.m_Transform->position = offset;

	// Dash Cooldown
	if (m_DashCountdown < m_DashCooldown)
	{
		m_DashCountdown += deltaTime;
	}

	// Continuous Input
	OnKey(deltaTime);

	// Animation Functions
	HandleConditions(deltaTime);
	UpdateAnimation();

	// Debug Movement
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

	// Reset Jump capability
	if (m_RigidbodyPtr->isGrounded() && std::abs(m_RigidbodyPtr->GetVelocity().y) < m_JumpResetThreshold)
	{
		m_JumpsLeft = m_MaxJumps;
	}

	// Return if in hurt state
	if (m_State == State::Hurt) return;

	// Move left
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
	// Move Right
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
	case SDLK_z:			// JUMP
		if(CanJump())
		{
			Jump();
			m_JumpsLeft--;
			m_State = State::Jumping;
			m_AudioSource->AssignClip(AudioLibrary::GetClip(Audio::HeroJump));
		}
		break;
	case SDLK_x:			// ATTACK
		Attack();
		break;
	case SDLK_c:			// DASH
		if (CanDash())
		{
			Dash();
			m_DashCountdown = 0;
			m_AudioSource->AssignClip(AudioLibrary::GetClip(Audio::HeroDash));
		}
		break;
	case SDLK_a:			// FOCUS / CAST
		Heal();
		break;
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
	case SDLK_z:		// CUT JUMP
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

void InputActions::Dash() const
{
	m_RigidbodyPtr->SetVelocity(m_DashVelocity * float(m_RendererPtr->m_FlipX ? -1 : 1), 0);
}

void InputActions::Heal() const
{
	Knight* knight{ Knight::m_Instance };

	if (knight->m_CollectedShards >= m_ShardsToHeal)
	{
		knight->m_CollectedShards -= m_ShardsToHeal;
		knight->Heal(1);
	}
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
	m_AttackCountdown = AnimLibrary::GetAnimation(AnimType::Knight, "Attack1")->Length();
}

void InputActions::HandleConditions(const float& deltaTime)
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

	if (!name.empty()) m_GameObject->GetComponent<Animator>()->Play(name);
}
#pragma endregion