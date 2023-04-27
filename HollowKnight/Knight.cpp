#include "pch.h"
#include "Knight.h"

#include <Animator.h>
#include <Collider.h>
#include <SpriteRenderer.h>

#include "SpriteLibrary.h"
#include "InputActions.h"
#include "AnimLibrary.h"
#include "Camera.h"

Knight::Knight() : Actor(5),
m_ColliderSize{50, 70}
{
}

void Knight::Start()
{
	// Assign animation clips to animator
	m_GameObject->GetComponent<Animator>()->AssignClips(AnimLibrary::GetAnimations(AnimType::Knight));

	// Set rendered sprite & layer
	auto* sprite = m_GameObject->GetComponent<SpriteRenderer>();
	sprite->AssignSprite(SpriteLibrary::GetSprite(Sprite::Knight));
	sprite->SetLayer(IDrawable::s_MidLayer + 1);

	// Set collider size
	m_GameObject->GetComponent<Collider>()->SetSize(m_ColliderSize);

	// Set as camera target
	Camera::m_MainPtr->SetTarget(*m_Transform);

	// Add input actions component
	m_GameObject->AddComponent(new InputActions());
}

void Knight::OnDeath()
{
}

void Knight::OnCollisionEnter(const Collision& collision)
{
	Print(m_GameObject->m_Name, TextColor::Yellow);
	Print(" collided ", TextColor::Lightgreen);
	Print(collision.m_GameObject->m_Name + "\n", TextColor::Yellow);
}

void Knight::OnCollisionStay(const Collision& collision)
{

}

void Knight::OnCollisionExit(const Collision& collision)
{
	Print(m_GameObject->m_Name, TextColor::Yellow);
	Print(" exited ", TextColor::Red);
	Print(collision.m_GameObject->m_Name + "\n", TextColor::Yellow);
}
