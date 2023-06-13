#include "pch.h"
#include "AttackCollider.h"

#include <GameObject.h>
#include <Collider.h>

#include "AudioLibrary.h"
#include <AudioSource.h>
#include "Enemy.h"

void AttackCollider::Awake()
{
	if (m_AudioSource == nullptr)
	{
		m_AudioSource = m_GameObject->AddComponent(new AudioSource(false, false));
	}
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
		m_AudioSource->SetClip(AudioLibrary::GetClip(Audio::EnemyDamage));
	}
	m_AudioSource->SetClip(AudioLibrary::GetClip(Audio::HeroSword));
}
