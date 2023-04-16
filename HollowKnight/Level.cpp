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
#include "GameObject.h"
#include <Transform.h>
#include "Knight.h"
#include "Camera.h"
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
	// Setup camera
	const auto cam = new GameObject("Camera");
	cam->AddComponent(new Camera(GameSettings::s_Screen));

	// Setup level layers
	const int backgroundLayer{ 5 };
	const int platformsLayer{ 6 };
	const int foregroundLayer{ 12 };

	// Setup level textures
	m_Background = new GameObject("Background Image");
	SetupLevelObject(m_Background, Sprite::Background, backgroundLayer);

	m_Middleground = new GameObject("Middleground Image");
	SetupLevelObject(m_Middleground, Sprite::Middleground, IDrawable::s_MidLayer);

	// Test version. The level will be redone in final version
	m_Platforms = new GameObject("Platforms Image");
	SetupLevelObject(m_Platforms, Sprite::Platforms, platformsLayer);
	m_Platforms->m_Transform->position = m_PlatformPosition;
	// ----

	m_Foreground = new GameObject("Foreground Image");
	SetupLevelObject(m_Foreground, Sprite::Foreground, foregroundLayer);

	Camera::m_MainPtr->SetLevelBoundaries(m_Middleground->GetComponent<SpriteRenderer>()->GetBounds());

	// Set up Knight
	m_KnightPtr = new GameObject("Hollow Knight");
	m_KnightPtr->AddComponent(new Knight());

	m_KnightPtr->m_Transform->Translate(m_SpawnPoint);
}

void Level::Update(const float& deltaTime)
{
	IUpdatable::Invoke(&IUpdatable::Update, deltaTime);
}

void Level::Draw() const
{
	glPushMatrix();

	// Apply camera alteration to matrix
	IDrawable::InvokeAll(&IDrawable::CameraDraw);

	// Loop through Draw layers
	for (int layer = 0; layer < IDrawable::m_TotalLayerCount - 1; layer++)
	{
		glPushMatrix();

		if (layer == 5) // Background layer
		{
			glTranslatef(-Camera::m_MainPtr->GetPosition(m_BackgroundOffset).x, 0, 0);
		}
		if (layer == 12) // Foreground layer
		{
			glTranslatef(Camera::m_MainPtr->GetPosition(m_ForegroundOffset).x, 0, 0);
		}

		// Draw layer
		IDrawable::Invoke(&IDrawable::Draw, layer);

		glPopMatrix();
	}

	if (CORE::s_DebugMode)
	{
		// Draw Debug elements
		IDrawable::InvokeAll(&IDrawable::DebugDraw);
	}

	glPopMatrix();
}

void Level::SetupLevelObject(GameObject* object, const Sprite& sprite, const int& layer)
{
	const auto spriteRenderer = object->AddComponent(new SpriteRenderer());

	spriteRenderer->AssignSprite(SpriteLibrary::GetSprite(sprite));
	spriteRenderer->SetLayer(layer);

	object->m_Transform->position.x += spriteRenderer->GetBounds().width / 2;
	object->m_Transform->position.y += spriteRenderer->GetBounds().height / 2;
}