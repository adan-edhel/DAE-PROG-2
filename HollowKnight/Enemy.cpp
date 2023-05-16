#include "pch.h"
#include "Enemy.h"

Enemy::Enemy() : Actor(1)
{
}

void Enemy::Awake()
{
	Actor::Awake();
	m_GameObject->tag = Tag::Enemy;
}

void Enemy::OnDeath()
{
	//TODO: Spawn reward
}
