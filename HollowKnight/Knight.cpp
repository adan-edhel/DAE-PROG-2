#include "pch.h"
#include "Knight.h"
#include "Global.h"
#include "SpriteRenderer.h"

Knight::Knight() : Actor(5, "HollowKnight/Knight.png")
{
	gameGameObject.transform.AddComponent(new SpriteRenderer("HollowKnight/Knight.png", 12, 12));
	m_SpriteRenderer = gameGameObject.transform.GetComponent<SpriteRenderer>();

	Global::DrawPlayground.Connect(this, &Knight::Draw);
}

void Knight::Draw() const
{
	const float spriteSize{ 80 };
	Rectf slice{0, spriteSize, spriteSize, spriteSize };

	m_SpriteRenderer->Draw();
}

void Knight::Update(const float& deltaTime)
{

}

void Knight::OnDeath()
{
	m_AnimState = AnimState::Dying;
}