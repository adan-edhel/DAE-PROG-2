#include "pch.h"
#include "Knight.h"
#include "Global.h"
#include "SpriteRenderer.h"

Knight::Knight() : Actor(5)
{
	m_SpriteRenderer = dynamic_cast<SpriteRenderer*>
	(AddComponent(new SpriteRenderer("HollowKnight/Knight.png", 12, 12)));

	transform->position = Vector2(400, 0);
}

void Knight::Draw() const
{
	m_SpriteRenderer->Draw();
}

void Knight::Update(const float& deltaTime)
{

}

void Knight::OnDeath()
{
	m_AnimState = AnimState::Dying;
}