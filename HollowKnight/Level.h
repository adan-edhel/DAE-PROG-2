#pragma once
#include <GameObject.h>

#include "SpriteLibrary.h"

class Level final
{
public:
	Level(const std::string& levelName);
	Level(const Level& other) { m_KnightPtr = other.m_KnightPtr; }
	Level& operator=(const Level& other)
	{
		if (this != &other)
		{
			delete m_KnightPtr;
			m_KnightPtr = other.m_KnightPtr;
		}
		return *this;
	}
	~Level();

	void Update(const float& deltaTime);
	void Draw() const;

private:
	GameObject* m_KnightPtr{};

	GameObject* m_Background{};
	GameObject* m_Middleground{};
	GameObject* m_Foreground{};
	GameObject* m_Platforms{};

	const Vector2 m_SpawnPoint{ 2200, 3150 };
	const float m_BackgroundOffset{ 0.05 };
	const float m_ForegroundOffset{ 0.005 };

	const Vector2 m_PlatformPosition{ 8380, 2490 };

	void Initialize();
	void SetupLevelObject(GameObject* object, const Sprite& sprite, const int& layer);
};