#include "pch.h"
#include "Knight.h"
#include "EventSystem.h"
#include "SpriteRenderer.h"

Knight::Knight() : Actor(5), InputActions(m_GameObject)
{
	m_pSpriteRenderer = dynamic_cast<SpriteRenderer*>
	(AddComponent(new SpriteRenderer("HollowKnight/Knight.png", 12, 12)));

	m_pTransform->position = Vector2(600, 600);
}

void Knight::Update(const float& deltaTime)
{

}

void Knight::Draw() const
{
	m_pSpriteRenderer->Draw();
}

void Knight::OnDeath()
{
	m_AnimState = AnimState::Dying;
}