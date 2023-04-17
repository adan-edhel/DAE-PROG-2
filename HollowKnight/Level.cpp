#include "pch.h"
#include "Level.h"

// Misc
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
#include "Crawlid.h"
#include "SpriteLibrary.h"

Level::Level(const std::string& levelName) :
	m_KnightPtr{"Hollow Knight"},
	m_Crawlid{"Crawlid"},
	m_SpawnPoint{2200, 3150},
	m_BackgroundOffset{0.05f},
	m_ForegroundOffset{0.005f},
	m_PlatformPosition{8380, 2490}
{
	if (CORE::s_DebugMode)
	{
		Print("New Level: ", TextColor::Green);
		Print(levelName + '\n', TextColor::Yellow);
	}

	Initialize();
}

void Level::Initialize()
{
	const Vector2 CrawlidSpawnPoint{ 4386, 2331 };

	// Setup level layers
	const int backgroundLayer{ 5 };
	const int platformsLayer{ 6 };
	const int foregroundLayer{ 12 };

	// Setup level textures
	SetupLevelObject(m_Background, Sprite::Background, backgroundLayer);
	SetupLevelObject(m_Middleground, Sprite::Middleground, IDrawable::s_MidLayer);
	SetupLevelObject(m_Platforms, Sprite::Platforms, platformsLayer);
	SetupLevelObject(m_Foreground, Sprite::Foreground, foregroundLayer);
	m_Platforms.m_Transform->position = m_PlatformPosition;

	Camera::m_MainPtr->SetLevelBoundaries(m_Middleground.GetComponent<SpriteRenderer>()->GetBounds());

	// Set up Knight
	m_KnightPtr.AddComponent(new Knight());
	m_KnightPtr.m_Transform->Translate(m_SpawnPoint);

	// Set up Crawlid
	m_Crawlid.AddComponent(new Crawlid());
	m_Crawlid.m_Transform->position = CrawlidSpawnPoint;
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

void Level::SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer)
{
	const auto spriteRenderer = object.AddComponent(new SpriteRenderer());

	spriteRenderer->AssignSprite(SpriteLibrary::GetSprite(sprite));
	spriteRenderer->SetLayer(layer);

	object.m_Transform->position.x += spriteRenderer->GetBounds().width / 2;
	object.m_Transform->position.y += spriteRenderer->GetBounds().height / 2;
}