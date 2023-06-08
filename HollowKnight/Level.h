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
	Level(const Level& other)					= delete;	// copy constructor
	Level(Level&& other) noexcept				= delete;	// move constructor
	Level& operator=(const Level& other)		= delete;	// copy operator
	Level& operator=(Level&& other) noexcept	= delete;	// move operator

	void Update(const float& deltaTime);
	void Draw() const;

private:
	// Heads-up display
	HUDManager m_Hud{};
	GameObject m_Knight{ "Hollow Knight" };

	const Vector2 m_PlatformPosition{ 8380, 2490 };
	static const int m_NumberCrawlids{ 2 };
	const Vector2 m_PlayerSpawnPoint;
	const float m_BackgroundOffset;
	const float m_ForegroundOffset;

	// Crawlids
	std::array<GameObject, m_NumberCrawlids> m_Crawlids{
		string("Crawlid"),
		string("Crawlid 2")};
	std::array<Vector2, m_NumberCrawlids> m_CrawlidSpawnPositions{
		Vector2(4386, 2331),
		Vector2(7000, 2340)};

	// Level Sprites
	GameObject m_Background		{ string("Background") };
	GameObject m_Middleground	{ string("Middleground") };
	GameObject m_Foreground		{ string("Foreground") };
	GameObject m_Platforms		{ string("Platform") };

	void Initialize();
	void SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer);
};
