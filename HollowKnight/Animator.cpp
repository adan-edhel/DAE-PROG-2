#include "pch.h"
#include "Animator.h"

namespace AmrothFramework
{
	Animator::Animator() :
	m_SpriteRenderer{m_Transform->GetComponent<SpriteRenderer>()},
	m_Sprite{m_SpriteRenderer->GetSprite()}
	{
		if (m_SpriteRenderer == nullptr)
		{
			std::cout << "No SpriteRenderer attached to object. \n";
		}
	}

	void Animator::Draw(Animation& anim) const
	{
		m_SpriteRenderer->Draw();
	}
}