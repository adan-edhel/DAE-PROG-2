#include "pch.h"
#include "Knight.h"

Knight::Knight() : Actor(5, "HollowKnight/Knight.png")
{

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

	m_Sheet.Draw(transform->position, slice);

	Actor::Draw();
}

void Knight::Update(float deltaTime)
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