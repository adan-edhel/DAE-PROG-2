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

void Animator::Play(Animation*) const
{
	
}

void Animator::Update(const float& deltaTime)
{

}