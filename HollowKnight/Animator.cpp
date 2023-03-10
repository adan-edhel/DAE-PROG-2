#include "pch.h"
#include "Animator.h"

namespace AmrothFramework
{
	Animator::Animator() :
	m_SpriteRenderer{m_Transform->GetComponent<SpriteRenderer>()}
	{
		if (m_SpriteRenderer == nullptr)
		{
			std::cout << "No SpriteRenderer attached to object. \n";
		}
	}
}