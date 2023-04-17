#pragma once
#include <GameObject.h>
#include "SpriteLibrary.h"

class Level final
{
public:
	Level(const std::string& levelName);
	~Level() = default;
	Level(const Level& other) = default;
	Level& operator=(const Level& other) = default;
	void Update(const float& deltaTime);
	void Draw() const;

private:
	GameObject m_KnightPtr;
	GameObject m_Crawlid;

	GameObject m_Background{};
	GameObject m_Middleground{};
	GameObject m_Foreground{};
	GameObject m_Platforms{};

	const Vector2 m_SpawnPoint;
	const float m_BackgroundOffset;
	const float m_ForegroundOffset;

	const Vector2 m_PlatformPosition;

	void Initialize();
	void SetupLevelObject(GameObject& object, const Sprite& sprite, const int& layer);
};