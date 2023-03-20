#include "pch.h"
#include "Level.h"

#include "../Engine/AmrothUtils.h"

// Interfaces
#include "IDrawEvent.h"
#include "IUpdateEvent.h"
#include "InputActions.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include "Transform.h"
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
	m_KnightPtr->AddComponent(new SpriteRenderer("HollowKnight/Knight.png", 12, 12));

	//TODO: Fix delete errors
	//m_KnightPtr->AddComponent(new Knight());
	//m_KnightPtr->AddComponent(new Rigidbody2D());
	//m_KnightPtr->AddComponent(new InputActions());

	m_KnightPtr->m_Transform->position = Vector2(600, 600);
}

void Level::Update(const float& deltaTime)
{
	IUpdateEvent::Invoke(&IUpdateEvent::Update, deltaTime);
}

void Level::Draw() const
{
	IDrawEvent::Invoke(&IDrawEvent::DrawBackground);
	IDrawEvent::Invoke(&IDrawEvent::DrawMidground);
	IDrawEvent::Invoke(&IDrawEvent::DrawForeground);

	IDrawEvent::Invoke(&IDrawEvent::DrawUserInterface);
}

Level::~Level()
{
	delete m_KnightPtr;
}