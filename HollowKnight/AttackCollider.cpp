#include "pch.h"
#include "AttackCollider.h"

#include <GameObject.h>
#include <Collider.h>
#include "Enemy.h"

void AttackCollider::OnCollisionEnter(const Collision& collision)
{
	if (collision.m_GameObject->CompareTag(Tag::Enemy))
	{
		collision.m_GameObject->GetComponent<Enemy>()->OnDamage();
	}
}
