#include "pch.h"
#include "Knight.h"

// Libraries
#include "SpriteLibrary.h"
#include "AudioLibrary.h"
#include "AnimLibrary.h"

// Components
#include <Animator.h>
#include <Collider.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>
#include <AudioListener.h>
#include <AudioSource.h>
#include <Camera.h>
#include <CORE.h>

#include "HUDManager.h"
#include "InputActions.h"

Knight::Knight() : Actor(5),
	m_ColliderSize{50, 70}
{
	if (m_Instance == nullptr) { m_Instance = this; }
}

Knight::~Knight()
{
	if (m_Instance == this) m_Instance = nullptr;
}

void Knight::Start()
{
	// Update HUD health values
	HUDManager::GetInstance().UpdateHealthBar(GetHealth());

	// Assign animation clips to animator
	m_GameObject->AddComponent(new Animator())->AssignClips(AnimLibrary::GetAnimations(AnimType::Knight));

	// Set rendered sprite & layer
	SpriteRenderer* spriteRenderer = m_GameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->AssignSprite(SpriteLibrary::GetSprite(Sprite::Knight));
	spriteRenderer->SetLayer(int(IDrawable::Layers::Knight));

	// Assign rigidbody reference
	m_RigidbodyPtr = m_GameObject->AddComponent(new Rigidbody2D);

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	// Set as camera target
	Camera::m_MainPtr->SetTarget(*m_Transform);

	// Add input actions component
	m_GameObject->AddComponent(new InputActions());
	// Add audio listener component
	m_GameObject->AddComponent(new AudioListener());

	// Set up audio sources
	if (m_FootStepSource == nullptr)
	{
		m_FootStepSource = m_GameObject->AddComponent(new AudioSource(true, false, true));
		m_FootStepSource->AssignClip(AudioLibrary::GetClip(Audio::HeroFootstep));
		m_FootStepSource->Pause();
	}
	if (m_AudioSource == nullptr)
	{
		m_AudioSource = m_GameObject->AddComponent(new AudioSource(false, false));
	}
}

void Knight::Update(const float& deltaTime)
{
	Actor::Update(deltaTime);
	HUDManager::GetInstance().UpdatePositionText(m_Transform->position);

	HandleWalkAudio();
	HandleGroundImpact();

	// Store Previous Velocity
	m_VelocityUpdateTimer += deltaTime;
	if (m_VelocityUpdateTimer >= m_VelocityUpdateInterval)
	{
		m_StoredVelocity = m_RigidbodyPtr->GetVelocity();
		m_VelocityUpdateTimer = 0;
	}
}

void Knight::HandleGroundImpact() const
{
	// Return if grounded
	if (!m_RigidbodyPtr->isGrounded()) return;

	// If soft impact
	if (m_StoredVelocity.y < -m_SoftImpactThreshold)
	{
		// If hard impact
		if (m_StoredVelocity.y < -m_HardImpactThreshold)
		{
			Camera::m_MainPtr->SetShake();
			m_AudioSource->AssignClip(AudioLibrary::GetClip(Audio::HeroLandHard));
		}
		else
		{
			m_AudioSource->AssignClip(AudioLibrary::GetClip(Audio::HeroLandSoft));
		}

		// Print impact info
		if (CORE::s_DebugMode)
		{
			Print("Impact velocity: " + std::to_string(m_StoredVelocity.y) + "\n");
		}
	}
}

void Knight::HandleWalkAudio() const
{
	if (m_RigidbodyPtr->isGrounded())
	{
		if (std::abs(m_RigidbodyPtr->GetVelocity().x) > m_WalkSoundThreshold)
		{
			m_FootStepSource->Resume();
			return;
		}
	}
	m_FootStepSource->Pause();
}

void Knight::OnDamage()
{
	Actor::OnDamage();
	HUDManager::GetInstance().UpdateHealthBar(GetHealth());
}

void Knight::OnDeath()
{
	//TODO: remove coins

	m_RigidbodyPtr->SetVelocity(0, 0);
	m_Transform->position = m_SpawnPosition;
	Heal(m_MaxHealth);
}

void Knight::OnCollisionEnter(const Collision& collision)
{
	if (collision.m_GameObject->CompareTag(Tag::Enemy))
	{
		OnDamage();

		// Knockback
		const Vector2 direction{ collision.m_Transform->position - m_Transform->position };
		m_GameObject->GetComponent<Rigidbody2D>()->AddForce(Vector2(-direction.Normalized() * m_KnockbackForce));
	}
	if (collision.m_GameObject->CompareTag(Tag::Coin))
	{
		//TODO: Earn coins
		m_AudioSource->AssignClip(AudioLibrary::GetClip(Audio::SoulPickup));
		delete collision.m_GameObject;
	}
}
