#include "Animator.h"

#include "GameObject.h"
#include "SpriteRenderer.h"


Animator::Animator() : Component("Animator")
{
}

void Animator::Awake()
{
	m_pSpriteRenderer = m_GameObject->GetComponent<SpriteRenderer>();
}

void Animator::Play(Animation*) const
{
	
}

void Animator::Update(const float& deltaTime)
{

}