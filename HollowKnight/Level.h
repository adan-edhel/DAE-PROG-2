#pragma once
#include <GameObject.h>
#include "SpriteLibrary.h"
#include "HUDManager.h"

#include <array>


class Level final
{
public:
	Level(const std::string& levelName);					// constructor
	~Level()									= default;	// destructor
	Level(const Level& other)					= delete;	// copy
	Level(Level&& other) noexcept				= delete;	// move
	Level& operator=(const Level& other)		= delete;	// copy operator
	Level& operator=(Level&& other) noexcept	= delete;	// move operator

	void Update(const float& deltaTime);
	void Draw() const;

private:
	HUDManager m_Hud{};

	static const int m_NumberCrawlids{ 2 };

	GameObject m_KnightPtr{"Hollow Knight"};
	std::array<GameObject, m_NumberCrawlids> m_Crawlids{
		string("Crawlid"),
		string("Crawlid 2")};

	const Vector2 m_PlayerSpawnPoint;
	std::array<Vector2, m_NumberCrawlids> m_CrawlidSpawnPositions{
		Vector2(4386, 2331),
		Vector2(7000, 2340)};

	GameObject m_Background{ string("Background") };
	GameObject m_Middleground{ string("Middleground") };
	GameObject m_Foreground{ string("Foreground") };
	GameObject m_Platforms{ string("Platform") };

	const Vector2 m_PlatformPosition{8380, 2490};

	const float m_BackgroundOffset;
	const float m_ForegroundOffset;

	void Initialize();
	void SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer);
};
