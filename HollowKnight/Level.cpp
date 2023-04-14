#include "pch.h"
#include "Level.h"

// Misc
#include "GameSettings.h"
#include "CORE.h"

// Interfaces
#include "IDrawable.h"
#include "IUpdatable.h"
#include "InputActions.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include <Transform.h>
#include "Animator.h"
#include "Knight.h"
#include "Camera.h"
#include "Collider.h"
#include "SpriteLibrary.h"

Level::Level(const std::string& levelName)
{
	if (CORE::s_DebugMode)
	{
		Print("New Level: ", TextColor::Green);
		Print(levelName + '\n', TextColor::Yellow);
	}

	Start();
}

void Level::Start()
{
	levelRef = new Texture("HollowKnight/LevelRef.png");

	m_LevelVisuals = new GameObject("Level Visuals");
	m_LevelVisuals->AddComponent(new SpriteRenderer(SpriteLibrary::GetSprite(Sprite::Level)));
	m_LevelVisuals->m_Transform->position.x += m_LevelVisuals->GetComponent<SpriteRenderer>()->Bounds().x / 2;
	m_LevelVisuals->m_Transform->position.y += m_LevelVisuals->GetComponent<SpriteRenderer>()->Bounds().y / 2;

	// Set up camera
	auto* cam = new GameObject("Camera");
	Camera* camera = cam->AddComponent(new Camera(GameSettings::s_Screen));

	// Set up Knight
	m_KnightPtr = new GameObject("Hollow Knight");
	m_KnightPtr->AddComponent(new SpriteRenderer(SpriteLibrary::GetSprite(Sprite::Knight), 12, 12));
	m_KnightPtr->AddComponent(new Animator());
	m_KnightPtr->AddComponent(new Collider());
	m_KnightPtr->AddComponent(new Rigidbody2D());
	m_KnightPtr->AddComponent(new InputActions());
	m_KnightPtr->AddComponent(new Knight());

	m_KnightPtr->m_Transform->position = Vector2{ 2268, 2580 };

	// Assign camera target
	camera->SetTarget(*m_KnightPtr->m_Transform);
	camera->SetLevelBoundaries(Rectf(-10000, 0, 20000, 10000));
}

void Level::Update(const float& deltaTime)
{
	IUpdatable::Invoke(&IUpdatable::Update, deltaTime);
}

void Level::Draw() const
{
	glPushMatrix();

	IDrawable::Invoke(&IDrawable::CameraDraw);
	levelRef->Draw(Point2f(0, 0));
	IDrawable::Invoke(&IDrawable::Draw);

	if (CORE::s_DebugMode)
	{
		IDrawable::Invoke(&IDrawable::DebugDraw);
	}

	glPopMatrix();
}

Level::~Level()
{
	delete levelRef;

	delete m_KnightPtr;
	delete m_LevelVisuals;
	delete Camera::m_MainPtr->m_GameObject;
}