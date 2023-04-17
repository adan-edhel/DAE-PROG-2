#include "pch.h"
#include "Knight.h"

#include <Animator.h>
#include <Collider.h>
#include <SpriteRenderer.h>

#include "SpriteLibrary.h"
#include "InputActions.h"
#include "AnimLibrary.h"
#include "Camera.h"

Knight::Knight() : Actor(5)
{
}

void Knight::Awake()
{
	Actor::Awake();

	auto* sprite = m_GameObject->GetComponent<SpriteRenderer>();
	sprite->AssignSprite(SpriteLibrary::GetSprite(Sprite::Knight));
	sprite->SetLayer(IDrawable::s_MidLayer + 1);

	m_GameObject->GetComponent<Collider>()->SetSize(colliderSize);

	Camera::m_MainPtr->SetTarget(*m_Transform);

	m_GameObject->AddComponent(new InputActions());

	auto* anim = m_GameObject->GetComponent<Animator>();
	anim->AssignClips(AnimLibrary::GetAnimations(AnimType::Knight));
	anim->Play("Walk");
}

void Knight::OnDeath()
{
}