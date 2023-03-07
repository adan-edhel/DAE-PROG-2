#include "pch.h"
#include "Knight.h"
#include "Delegates.h"

Knight::Knight() : Actor(5, "HollowKnight/Knight.png")
{
	Delegates::DrawObjects.Connect(this, &Knight::Draw);
}

void Knight::Draw() const
{
	const float spriteSize{ 80 };
	Rectf slice{0, spriteSize, spriteSize, spriteSize };

	switch (m_AnimState)
	{
	case AnimState::Idle:
		slice.left = 0;
		break;
	case AnimState::Walking:
		break;
	case AnimState::Attacking:
		break;
	case AnimState::Jumping:
		break;
	case AnimState::Hurt:
		break;
	case AnimState::Dying:
		break;
	}

	m_Sheet.Draw(gameObject->transform->position.ToPoint2f(), slice);

	Actor::Draw();
}

void Knight::Update(const float& deltaTime)
{
	Actor::Update(deltaTime);
}

void Knight::OnDeath()
{
	Actor::OnDeath();
	m_AnimState = AnimState::Dying;
}

Knight::~Knight()
{
	
}