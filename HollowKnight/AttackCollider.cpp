#include "pch.h"
#include "AttackCollider.h"

#include <GameObject.h>
#include <Collider.h>

#include "AudioLibrary.h"
#include <SoundEffect.h>
#include "Enemy.h"

void AttackCollider::Awake()
{
	m_EnemyHit = false;
}

void AttackCollider::OnDisable()
{
	PlaySound();
}

void AttackCollider::OnCollisionEnter(const Collision& collision)
{
	if (collision.m_GameObject->CompareTag(Tag::Enemy))
	{
		collision.m_GameObject->GetComponent<Enemy>()->OnDamage();
		m_EnemyHit = true;
	}
}

void AttackCollider::PlaySound() const
{
	if (m_EnemyHit)
	{
		AudioLibrary::GetClip(Audio::EnemyDamage)->PlayOnce();
	}
	AudioLibrary::GetClip(Audio::HeroSword)->PlayOnce();
}
