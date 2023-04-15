#include "pch.h"
#include "Knight.h"

#include <Collider.h>
#include <SpriteRenderer.h>

#include "Camera.h"
#include "InputActions.h"
#include "SpriteLibrary.h"

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
}

void Knight::OnDeath()
{
	m_AnimState = AnimState::Dying;
}