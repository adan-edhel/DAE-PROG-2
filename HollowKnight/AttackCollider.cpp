#include "pch.h"
#include "AttackCollider.h"

#include "AudioLibrary.h"

#include <GameObject.h>
#include <AudioSource.h>
#include <Rigidbody2D.h>
#include <Collider.h>

#include "Enemy.h"
#include "Knight.h"

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

		const Vector2 direction{ collision.m_Transform->position - Knight::m_Instance->m_Transform->position };
		collision.m_GameObject->GetComponent<Rigidbody2D>()->AddForce(Vector2(direction.Normalized() * m_KnockbackForce));

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
