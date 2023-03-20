#include "pch.h"
#include "Knight.h"

Knight::Knight() : Actor(5)
{
}

void Knight::OnDeath()
{
	m_AnimState = AnimState::Dying;
}