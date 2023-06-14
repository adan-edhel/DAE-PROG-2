#include "pch.h"
#include "Enemy.h"

#include <Animator.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>

Enemy::Enemy() : Actor(1)
{
}

void Enemy::Awake()
{
	Actor::Awake();
	m_GameObject->tag = Tag::Enemy;

	// Assign component pointers
	m_SpriteRendererPtr = m_GameObject->GetComponent<SpriteRenderer>();
	m_RigidbodyPtr = m_GameObject->AddComponent(new Rigidbody2D());
	m_AnimatorPtr = m_GameObject->AddComponent(new Animator());
}

void Enemy::Update(const float& deltaTime)
{
	HandleStates(deltaTime);
	HandleAnimation();
}

void Enemy::OnDeath()
{
	m_SpriteRendererPtr->SetLayer(int(IDrawable::Layers::Actors) - 1);
	//TODO: Spawn reward (optionally)
}
