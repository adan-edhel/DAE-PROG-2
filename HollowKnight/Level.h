#pragma once
#include <GameObject.h>
#include <array>

#include "SpriteLibrary.h"
#include "HUDManager.h"

class AudioSource;

class Level final
{
public:
	Level(const std::string& levelName);
	~Level(); // No dynamic memory

	void Update(const float& deltaTime);
	void Draw() const;

private:
	// Heads-up display
	HUDManager m_Hud{};
	GameObject m_Knight{ "Hollow Knight" };

	const Vector2 m_PlatformPosition{ 8380, 2490 };
	static const int m_NumberCrawlids{ 2 };
	static const int m_NumberVengeflies{ 4 };
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

	// Vengeflies
	std::array<GameObject, m_NumberVengeflies> m_Vengeflies{
		string("Vengefly 1"),
		string("Vengefly 2")};
	std::array<Vector2, m_NumberVengeflies> m_VengeflyPositions{
		Vector2(8300, 2626),
		Vector2(2200, 2700)};

	// Level Sprites
	GameObject m_Background{};
	GameObject m_Middleground{};
	GameObject m_Foreground{};
	GameObject m_Platforms{};

	// Level Audio
	GameObject m_AudioSource{};
	AudioSource* m_BlizzardAmbience{};

	void Initialize();
	void SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer);
};