#include "pch.h"
#include "Level.h"

// Interfaces
#include "IDrawable.h"
#include "IUpdatable.h"
#include "InputActions.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"
#include "Knight.h"

Level::Level(const std::string& levelName)
{
	Print("New Level: ", TextColor::Green);
	Print(levelName + '\n', TextColor::Yellow);

	Start();
}

void Level::Start()
{
	m_KnightPtr = new GameObject("Hollow Knight");
	m_KnightPtr->AddComponent(new Rigidbody2D());
	m_KnightPtr->AddComponent(new SpriteRenderer());
	m_KnightPtr->AddComponent(new Animator());

	m_KnightPtr->AddComponent(new InputActions());
	m_KnightPtr->AddComponent(new Knight());

}

void Level::Update(const float& deltaTime)
{
	IUpdatable::Invoke(&IUpdatable::Update, deltaTime);
}

void Level::Draw() const
{
	IDrawable::Invoke(&IDrawable::Draw);
}

Level::~Level()
{
	delete m_KnightPtr;
}