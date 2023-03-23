#include "pch.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Animator::Animator() : Component("Animator")
{
	if (m_pSpriteRenderer == nullptr)
	{
		std::cout << "No SpriteRenderer attached to object. \n";
	}
}

void Animator::Draw() const
{
	//m_pSpriteRenderer->Draw();
}

void Animator::Update(const float& deltaTime)
{

}