#include "pch.h"
#include "Level.h"

// Misc
#include <CORE.h>

// Libraries
#include "AudioLibrary.h"
#include "SpriteLibrary.h"

// Interfaces
#include <IDrawable.h>
#include <IUpdatable.h>

// Components
#include <SpriteRenderer.h>
#include <AudioSource.h>
#include <GameObject.h>
#include <Transform.h>
#include <Camera.h>

#include "Knight.h"
#include "Crawlid.h"
#include "Vengefly.h"

Level::Level(const std::string& levelName) :
	m_PlayerSpawnPoint{2200, 3150},
	m_BackgroundOffset{0.05f},
	m_ForegroundOffset{0.005f}
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
	// Setup level textures
	SetupLevelObject(m_Background,	Sprite::Background,	 int(IDrawable::Layers::Background));
	SetupLevelObject(m_Middleground, Sprite::Middleground,int(IDrawable::Layers::Middleground));
	SetupLevelObject(m_Platforms,	Sprite::Platforms,	 int(IDrawable::Layers::Platforms));
	SetupLevelObject(m_Foreground,	Sprite::Foreground,	 int(IDrawable::Layers::Foreground));
	m_Platforms.m_Transform->position = m_PlatformPosition;

	Camera::m_MainPtr->SetLevelBoundaries(m_Middleground.GetComponent<SpriteRenderer>()->GetBounds());

	// Set up Knight
	m_Knight.AddComponent(new Knight());
	m_Knight.m_Transform->Translate(m_PlayerSpawnPoint);

	// Set up Crawlids
	if (!m_Crawlids.empty())
	{
		for (int i = 0; i < m_Crawlids.size(); i++)
		{
			m_Crawlids[i].AddComponent(new Crawlid());
			m_Crawlids[i].m_Transform->position = m_CrawlidSpawnPositions[i];
		}
	}

	// Set up Vengeflies
	//if (!m_Vengeflies.empty())
	//{
	//	for (int i = 0; i < m_Crawlids.size(); i++)
	//	{
	//		m_Vengeflies[i].AddComponent(new Vengefly());
	//		m_Vengeflies[i].m_Transform->position = m_VengeflySpawnPositions[i];
	//	}
	//}

	m_Vengefly.AddComponent(new Vengefly());
	m_Vengefly.m_Transform->position = Vector2(8300, 2626);

	// Play Ambience audio
	if (m_BlizzardAmbience == nullptr)
	{
		m_BlizzardAmbience = m_AudioSource.AddComponent(new AudioSource(true, false));
	}
	//m_BlizzardAmbience->SetClip(AudioLibrary::GetClip(Audio::Blizzard));
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

		if (layer == int(IDrawable::Layers::Background))
		{
			glTranslatef(-Camera::m_MainPtr->GetPosition(m_BackgroundOffset).x, 0, 0);
		}
		if (layer == int(IDrawable::Layers::Foreground))
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

	IDrawable::InvokeAll(&IDrawable::UIDraw);
}

void Level::SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer)
{
	SpriteRenderer* spriteRenderer = object.AddComponent(new SpriteRenderer());

	spriteRenderer->AssignSprite(SpriteLibrary::GetSprite(sprite));
	spriteRenderer->SetLayer(layer);

	object.m_Transform->position.x += spriteRenderer->GetBounds().width / 2;
	object.m_Transform->position.y += spriteRenderer->GetBounds().height / 2;
}