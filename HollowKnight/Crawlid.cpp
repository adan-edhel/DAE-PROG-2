#include "pch.h"
#include "Crawlid.h"

#include "AnimLibrary.h"
#include "SpriteLibrary.h"

#include <Collider.h>
#include <Animator.h>
#include <Animation.h>
#include <AudioSource.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>

#include "AudioLibrary.h"

Crawlid::Crawlid() :
	m_FootSteps{"Audio/Game/Enemies/crawler.wav"},
	m_State{ State::Walking },
	m_Direction{ Direction::Left },
	m_ColliderSize{ 110, 80 },
	m_WalkSpeed{ 20 },
	m_TurnInterval{5}
{
}

void Crawlid::Start()
{
	// Assign component pointers
	m_AnimatorPtr = m_GameObject->GetComponent<Animator>();
	m_Rigidbody = m_GameObject->GetComponent<Rigidbody2D>();
	m_SpriteRend = m_GameObject->GetComponent<SpriteRenderer>();
	m_AudioSource = m_GameObject->AddComponent(new AudioSource(true));

	// Assign animation clips to animator
	m_AnimatorPtr->AssignClips(AnimLibrary::GetAnimations(AnimType::Crawlid));

	// Set rendered sprite & layer
	auto* sprite = m_GameObject->GetComponent<SpriteRenderer>();
	sprite->AssignSprite(SpriteLibrary::GetSprite(Sprite::Crawlid));

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	//TODO: refactor library
	m_AudioSource->SetClip(&m_FootSteps);
}

void Crawlid::Update(const float& deltaTime)
{
	if (m_State == State::Dying) return;

	ManageStates(deltaTime);
	UpdateAnimation();
}

void Crawlid::OnDeath()
{
	m_AudioSource->Stop();
}

void Crawlid::ManageStates(const float& deltaTime)
{
	if (GetHealth() <= 0)
	{
		m_State = State::Dying;
		m_GameObject->GetComponent<Collider>()->m_IsEnabled = false;
	}

	switch (m_State)
	{
		case State::Walking:
			Walk(deltaTime);
			Turn(deltaTime);
			break;
		case State::Turning:
			if (m_AnimatorPtr->Current()->Finished())
			{
				if (m_Direction == Direction::Left)
				{
					m_Direction = Direction::Right;
					m_SpriteRend->m_FlipX = true;
				}
				else
				{
					m_Direction = Direction::Left;
					m_SpriteRend->m_FlipX = false;
				}

				m_State = State::Walking;
				m_TurnCounter = 0;
			}
			break;
	}
}

void Crawlid::Walk(const float& deltaTime) const
{
	m_Rigidbody->AddForce(Vector2
	(m_Direction == Direction::Left ? -m_WalkSpeed : m_WalkSpeed, 0) * deltaTime);
}

void Crawlid::Turn(const float& deltaTime)
{
	if (m_State != State::Turning) m_TurnCounter += deltaTime;

	if (m_TurnCounter >= m_TurnInterval + RandomRange(-3, 3))
	{
		m_State = State::Turning;
	}
}

void Crawlid::UpdateAnimation() const
{
	std::string name{};

	switch (m_State)
	{
	case State::Walking:
		name = "Walk";
		break;
	case State::Turning:
		name = "Turn";
		break;
	case State::Dying:
		name = "Die";
		break;
	}

	if (!name.empty()) m_AnimatorPtr->Play(name);
}