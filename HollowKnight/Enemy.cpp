#include "pch.h"
#include "Enemy.h"

#include <Animator.h>
#include <Rigidbody2D.h>
#include <SpriteRenderer.h>

#include "MaskShard.h"

Enemy::Enemy() : Actor(1)
{
}

void Enemy::Awake()
{
	Actor::Awake();
	m_GameObject->m_Tag = Tag::Enemy;

	// Assign component pointers
	m_SpriteRendererPtr = m_GameObject->GetComponent<SpriteRenderer>();
	m_RigidbodyPtr = m_GameObject->AddComponent(new Rigidbody2D());
	m_AnimatorPtr = m_GameObject->AddComponent(new Animator());

	m_SpriteRendererPtr->SetLayer(int(IDrawable::Layers::Enemies));
}

void Enemy::Update(const float& deltaTime)
{
	HandleStates(deltaTime);
	HandleAnimation();
}

void Enemy::OnDeath()
{
	// Spawn Shards
	for (int i = 0; i < m_ShardDrops; i++)
	{
		GameObject* shard = new GameObject();
		shard->AddComponent(new MaskShard());
		shard->m_Transform->position = m_Transform->position;
	}
}
