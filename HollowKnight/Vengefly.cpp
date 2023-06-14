#include "pch.h"
#include "Vengefly.h"
#include <AmrothUtils.h>

#include "SpriteLibrary.h"
#include "AnimLibrary.h"

#include <Collider.h>
#include <Animator.h>
#include <Animation.h>
#include <AudioSource.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>

#include "Knight.h"

Vengefly::Vengefly() :
	m_WingSounds{"Audio/Game/Enemies/buzzer_fly.ogg"}
{
	m_StartleSounds.push_back(new SoundEffect("Audio/Game/Enemies/buzzer_startle_01.wav"));
	m_StartleSounds.push_back(new SoundEffect("Audio/Game/Enemies/buzzer_startle_02.wav"));
	m_StartleSounds.push_back(new SoundEffect("Audio/Game/Enemies/buzzer_startle_03.wav"));
}

Vengefly::~Vengefly()
{
	for (const SoundEffect* const& audio : m_StartleSounds)
	{
		delete audio;
	}
}

void Vengefly::Start()
{
	// Assign component pointers
	m_StartleSourcePtr = m_GameObject->AddComponent(new AudioSource(false));
	m_FlySourcePtr = m_GameObject->AddComponent(new AudioSource(true));

	// Assign animation clips to animator
	m_AnimatorPtr->AssignClips(AnimLibrary::GetAnimations(AnimType::Vengefly));

	// Set rendered sprite & layer
	m_SpriteRendererPtr->AssignSprite(SpriteLibrary::GetSprite(Sprite::Vengelfy));

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	// Set rigidbody to static
	m_RigidbodyPtr->m_GravityEnabled = false;

	m_FlySourcePtr->SetClip(&m_WingSounds);
}

void Vengefly::Update(const float& deltaTime)
{
	if (!IsAlive()) return;
	Enemy::Update(deltaTime);
}

void Vengefly::OnDamage()
{
	Enemy::OnDamage();
	m_State = State::Startled;
}

void Vengefly::OnDeath()
{
	Enemy::OnDeath();

	HandleAnimation();
	m_FlySourcePtr->Stop();
	m_RigidbodyPtr->m_GravityEnabled = true;
	m_GameObject->GetComponent<Collider>()->m_IsEnabled = false;
}

void Vengefly::Fly(const float& deltaTime) const
{
	if (m_State == State::Startled) return;

	if (m_State == State::Charging)
	{
		Vector2::MoveTowards(m_Transform->position, Knight::m_Instance->m_Transform->position, m_AttackSpeed * deltaTime);
		return;
	}

	m_RigidbodyPtr->AddForce(Vector2(m_Direction == Direction::Left ? -m_MoveSpeed : m_MoveSpeed, 0) * deltaTime);
}

void Vengefly::Turn(const float& deltaTime)
{
	if (m_State != State::Turning) m_TurnCounter += deltaTime;

	if (m_TurnCounter >= m_BaseTurnInterval + RandomRange(-m_TurnIntervalOffset, m_TurnIntervalOffset))
	{
		m_State = State::Turning;
	}
}

bool Vengefly::PlayerInAttackRange() const
{
	return GetDistanceBetween(m_Transform->position.ToPoint2f(), Knight::m_Instance->m_Transform->position.ToPoint2f()) <= m_AttackDistance;
}

bool Vengefly::PlayerOnLeft() const
{
	return Knight::m_Instance->m_Transform->position.x < m_Transform->position.x;
}

SoundEffect* Vengefly::GetRandomStartleSound() const
{
	return m_StartleSounds[RandomRange(0, int(m_StartleSounds.size()) - 1)];
}

void Vengefly::HandleStates(const float& deltaTime)
{
	if (PlayerInAttackRange() && m_State != State::Charging)
	{
		m_FlySourcePtr->Pause();
		if (!m_StartleSourcePtr->IsPlaying())
		{
			m_StartleSourcePtr->SetClip(GetRandomStartleSound());
		}
		m_State = State::Startled;
		m_Hostile = true;
	}

	switch (m_State)
	{
	case State::Flying:
		Fly(deltaTime);
		Turn(deltaTime);
		break;
	case State::Turning:
		if (m_AnimatorPtr->Current()->m_Name == "Turn")
		{
			if (m_AnimatorPtr->Current()->Finished())
			{
				if (m_Direction == Direction::Left)
				{
					m_Direction = Direction::Right;
					m_SpriteRendererPtr->m_FlipX = true;
				}
				else
				{
					m_Direction = Direction::Left;
					m_SpriteRendererPtr->m_FlipX = false;
				}

				m_State = State::Flying;
				m_TurnCounter = 0;
			}
		}
		break;
	case State::Startled:
		if (m_AnimatorPtr->Current()->m_Name == "Startle")
		{
			if (m_AnimatorPtr->Current()->Finished())
			{
				m_State = PlayerInAttackRange() ? State::Charging : State::Flying;
				m_FlySourcePtr->Resume();
			}
		}
		break;
	case State::Charging:
		Fly(deltaTime);
		if (m_Hostile)
		{
			m_SpriteRendererPtr->m_FlipX = PlayerOnLeft() ? false : true;
		}
		if (!PlayerInAttackRange() && !m_Hostile) m_State = State::Flying;
		break;
	}
}

void Vengefly::HandleAnimation() const
{
	// return if animator is nullptr
	if (m_AnimatorPtr == nullptr) return;
	// return if animator has no clips
	if (!m_AnimatorPtr->IsLoaded()) return;

	// Return if actor is dead
	if (!IsAlive())
	{
		m_AnimatorPtr->Play("Die");
		return;
	}

	// Assign animation based on state
	std::string name{};
	switch (m_State)
	{
	case State::Flying:
		name = "Fly";
		break;
	case State::Turning:
		name = "Turn";
		break;
	case State::Startled:
		name = "Startle";
		break;
	case State::Charging:
		name = "Charge";
		break;
	}
	// Assign animation
	if (!name.empty()) m_AnimatorPtr->Play(name);
}
