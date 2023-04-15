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

	Initialize();
}

Level::~Level()
{
	delete Camera::m_MainPtr->m_GameObject;

	delete m_Background;
	delete m_Middleground;
	delete m_Foreground;
	delete m_Platforms;

	delete m_KnightPtr;
}

void Level::Initialize()
{
	SpawnLevel();

	m_KnightPtr->m_Transform->position = Vector2{ 2268, 2700 };
}

void Level::Update(const float& deltaTime)
{
	IUpdatable::Invoke(&IUpdatable::Update, deltaTime);
}

void Level::Draw() const
{
	glPushMatrix();

	IDrawable::Invoke(&IDrawable::CameraDraw);
	IDrawable::Invoke(&IDrawable::Draw);

	if (CORE::s_DebugMode)
	{
		IDrawable::Invoke(&IDrawable::DebugDraw);
	}

	glPopMatrix();
}

void Level::SpawnLevel()
{
	// Set up camera
	auto* cam = new GameObject("Camera");
	Camera* camera = cam->AddComponent(new Camera(GameSettings::s_Screen));

	// Set up background texture
	m_Background = new GameObject("Background Image");
	auto* spriteRnd = m_Background->AddComponent(new SpriteRenderer());
	spriteRnd->AssignSprite(SpriteLibrary::GetSprite(Sprite::Background));
	m_Background->m_Transform->position.x += spriteRnd->GetBounds().width / 2;
	m_Background->m_Transform->position.y += spriteRnd->GetBounds().height / 2;

	// Set up middleground texture
	m_Middleground = new GameObject("Middleground Image");
	spriteRnd = m_Middleground->AddComponent(new SpriteRenderer());
	spriteRnd->AssignSprite(SpriteLibrary::GetSprite(Sprite::Middleground));
	m_Middleground->m_Transform->position.x += spriteRnd->GetBounds().width / 2;
	m_Middleground->m_Transform->position.y += spriteRnd->GetBounds().height / 2;

	// Set camera boundaries
	camera->SetLevelBoundaries(spriteRnd->GetBounds());

	// Set up foreground texture
	m_Foreground = new GameObject("Foreground Image");
	spriteRnd = m_Foreground->AddComponent(new SpriteRenderer());
	spriteRnd->AssignSprite(SpriteLibrary::GetSprite(Sprite::Foreground));
	m_Foreground->m_Transform->position.x += spriteRnd->GetBounds().width / 2;
	m_Foreground->m_Transform->position.y += spriteRnd->GetBounds().height / 2;

	// Set up middleground texture
	m_Platforms = new GameObject("Platforms Image");
	spriteRnd = m_Platforms->AddComponent(new SpriteRenderer());
	spriteRnd->AssignSprite(SpriteLibrary::GetSprite(Sprite::Platforms));
	m_Platforms->m_Transform->position.x += spriteRnd->GetBounds().width / 2;
	//m_Platforms->m_Transform->position.y += spriteRnd->GetBounds().height / 2;

	// Set up Knight
	m_KnightPtr = new GameObject("Hollow Knight");
	m_KnightPtr->AddComponent(new SpriteRenderer(SpriteLibrary::GetSprite(Sprite::Knight), 12, 12));
	m_KnightPtr->AddComponent(new Animator());
	m_KnightPtr->AddComponent(new Collider());
	m_KnightPtr->AddComponent(new Rigidbody2D());
	m_KnightPtr->AddComponent(new InputActions());
	m_KnightPtr->AddComponent(new Knight());

	// Assign camera target
	camera->SetTarget(*m_KnightPtr->m_Transform);
}