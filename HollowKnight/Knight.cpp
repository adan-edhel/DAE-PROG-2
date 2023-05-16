#include "pch.h"
#include "Knight.h"

#include <Animator.h>
#include <Collider.h>
#include <SpriteRenderer.h>
#include <Rigidbody2D.h>

#include "SpriteLibrary.h"
#include "InputActions.h"
#include "AnimLibrary.h"
#include "Camera.h"
#include "CORE.h"

#include "HUDManager.h"

Knight::Knight() : Actor(5),
m_ColliderSize{50, 70}
{
}

void Knight::Start()
{
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
	HUDManager::UpdatePlayerPosition(m_Transform->position);

	if (std::abs(m_RigidbodyPtr->GetVelocity().y) > m_ImpactThreshold) // TODO: Make sure this happens only on impact
	{
		if (CORE::s_DebugMode)
		{
			Print("Impact velocity: " + std::to_string(m_RigidbodyPtr->GetVelocity().y) + "\n");
		}
		Camera::m_MainPtr->SetShake();
	}
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
