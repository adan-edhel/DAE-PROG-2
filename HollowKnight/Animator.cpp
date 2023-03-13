#include "pch.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Animator::Animator() :
	m_pSpriteRenderer{ m_pTransform->GetComponent<SpriteRenderer>() },
	m_Sprite{ m_pSpriteRenderer->GetSprite() }
{
	if (m_pSpriteRenderer == nullptr)
	{
		std::cout << "No SpriteRenderer attached to object. \n";
	}
}

void Animator::Draw() const
{
	if (!m_pIsActive) return;

	m_pSpriteRenderer->Draw();
}