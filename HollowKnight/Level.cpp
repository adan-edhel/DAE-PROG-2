#include "pch.h"
#include "Level.h"

#include "GameSettings.h"

// Interfaces
#include "IDrawable.h"
#include "IUpdatable.h"
#include "InputActions.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include "Animator.h"
#include "Knight.h"
#include "Camera.h"

Level::Level(const std::string& levelName)
{
	if (GameSettings::s_DebugMode)
	{
		Print("New Level: ", TextColor::Green);
		Print(levelName + '\n', TextColor::Yellow);
	}

	Start();
}

void Level::Start()
{
	// Set up camera
	m_CameraPtr = new GameObject("Camera");
	Camera* camera = m_CameraPtr->AddComponent(
		new Camera(GameSettings::s_Screen));

	// Set up Knight
	m_KnightPtr = new GameObject("Hollow Knight");
	m_KnightPtr->AddComponent(new Rigidbody2D());
	m_KnightPtr->AddComponent(new SpriteRenderer());
	m_KnightPtr->AddComponent(new Animator());

	m_KnightPtr->AddComponent(new InputActions());
	m_KnightPtr->AddComponent(new Knight());

	// Assign camera target
	camera->SetTarget(*m_KnightPtr->m_Transform);
	camera->SetLevelBoundaries(Rectf(- 100, 0, 2000, 500));
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
	delete m_CameraPtr;
}