#include "pch.h"
#include "Crawlid.h"

// Libraries
#include "AnimLibrary.h"
#include "SpriteLibrary.h"

// Components
#include <Collider.h>
#include <Animator.h>
#include <Animation.h>
#include <AudioSource.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>

Crawlid::Crawlid() :
	m_FootSteps{"Audio/Game/Enemies/crawler.wav"}
{
}

void Crawlid::Start()
{
	// Assign component pointers
	m_AudioSourcePtr = m_GameObject->AddComponent(new AudioSource(true));

	// Assign animation clips to animator
	if (m_AnimatorPtr != nullptr)
	{
		m_AnimatorPtr->AssignClips(AnimLibrary::GetAnimations(AnimType::Crawlid));
	}

	// Set rendered sprite & layer
	if (m_SpriteRendererPtr != nullptr)
	{
		m_SpriteRendererPtr->AssignSprite(SpriteLibrary::GetSprite(Sprite::Crawlid));
	}

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	// Assign audio clip
	m_AudioSourcePtr->AssignClip(&m_FootSteps);
}

void Crawlid::Update(const float& deltaTime)
{
	if (!IsAlive()) return;
	Enemy::Update(deltaTime);
}

void Crawlid::OnDeath()
{
	Enemy::OnDeath();

	m_GameObject->GetComponent<Collider>()->m_IsEnabled = false;
	m_AudioSourcePtr->Stop();
	HandleAnimation();
}

void Crawlid::Walk(const float& deltaTime) const
{
	m_RigidbodyPtr->AddForce(Vector2
	(m_Direction == Direction::Left ? -m_MoveSpeed : m_MoveSpeed, 0) * deltaTime);
}

void Crawlid::Turn(const float& deltaTime)
{
	if (m_State != State::Turning) m_TurnCounter += deltaTime;

	if (m_TurnCounter >= m_BaseTurnInterval + RandomRange(-m_TurnIntervalOffset, m_TurnIntervalOffset))
	{
		m_State = State::Turning;
	}
}

void Crawlid::HandleStates(const float& deltaTime)
{
	switch (m_State)
	{
	case State::Walking:
		Walk(deltaTime);
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

				m_State = State::Walking;
				m_TurnCounter = 0;
			}
		}
		break;
	}
}

void Crawlid::HandleAnimation() const
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
	case State::Walking:
		name = "Walk";
		break;
	case State::Turning:
		name = "Turn";
		break;
	}
	if (!name.empty()) m_AnimatorPtr->Play(name);
}