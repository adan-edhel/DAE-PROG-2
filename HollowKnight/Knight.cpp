#include "pch.h"
#include "Knight.h"

#include <Animator.h>
#include <Collider.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>
#include "SpriteLibrary.h"
#include "InputActions.h"
#include "AnimLibrary.h"
#include "Camera.h"
#include "CORE.h"

#include "HUDManager.h"

Knight::Knight() : Actor(5),
	m_ColliderSize{50, 70},
	m_Walking{"HollowKnight/Audio/Game/Hero/hero_run_footsteps_stone.wav"},
	m_LandingSoft{"HollowKnight/Audio/Game/Hero/hero_land_soft.wav"},
	m_LandingHard{ "HollowKnight/Audio/Game/Hero/hero_land_hard.wav" }
{
}

void Knight::Start()
{
	// Update HUD health values
	HUDManager::GetInstance().UpdateHealthBar(GetHealth());

	// Assign animation clips to animator
	m_GameObject->GetComponent<Animator>()->AssignClips(AnimLibrary::GetAnimations(AnimType::Knight));

	// Set rendered sprite & layer
	SpriteRenderer* renderer = m_GameObject->GetComponent<SpriteRenderer>();
	renderer->AssignSprite(SpriteLibrary::GetSprite(Sprite::Knight));
	renderer->SetLayer(IDrawable::s_MidLayer + 1);

	// Assign rigidbody reference
	m_RigidbodyPtr = m_GameObject->GetComponent<Rigidbody2D>();

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	// Set as camera target
	Camera::m_MainPtr->SetTarget(*m_Transform);

	// Add input actions component
	m_GameObject->AddComponent(new InputActions());
}

void Knight::Update(const float& deltaTime)
{
	Actor::Update(deltaTime);
	HUDManager::GetInstance().UpdatePositionText(m_Transform->position);

	HandleWalkAudio();
	HandleGroundImpact();

	// Store Previous Velocity
	m_VelocityUpdateCounter += deltaTime;
	if (m_VelocityUpdateCounter >= m_VelocityUpdateInterval)
	{
		m_StoredVelocity = m_RigidbodyPtr->GetVelocity();
		m_VelocityUpdateCounter = 0;
	}
}

void Knight::HandleGroundImpact() const
{
	if (!m_RigidbodyPtr->isGrounded()) return;

	if (m_StoredVelocity.y < -m_SoftImpactThreshold)
	{
		if (m_StoredVelocity.y < -m_HardImpactThreshold)
		{
			Camera::m_MainPtr->SetShake();
			m_LandingHard.PlayOnce();
		}
		else
		{
			m_LandingSoft.PlayOnce();
		}

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
			if (!m_Walking.IsPlaying())
			{
				m_Walking.PlayOnce(-1);
			}
			return;
		}
	}
	m_Walking.Stop();
}

void Knight::OnDamage()
{
	Actor::OnDamage();
	HUDManager::GetInstance().UpdateHealthBar(GetHealth());
}

void Knight::OnDeath()
{
}

void Knight::OnCollisionEnter(const Collision& collision)
{
	if (collision.m_GameObject->CompareTag(Tag::Enemy))
	{
		OnDamage();

		// Knockback
		const Vector2 direction{ collision.m_Transform->position - m_Transform->position };
		m_GameObject->GetComponent<Rigidbody2D>()->AddForce(Vector2(-direction.Normalized() * 15));
	}
}

void Knight::OnCollisionStay(const Collision& collision)
{

}

void Knight::OnCollisionExit(const Collision& collision)
{

}
