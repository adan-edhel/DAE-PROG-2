#pragma once
#include "Vector2.h"

class GameObject;

class Level final
{
public:
	Level(const std::string& levelName);
	void Update(const float& deltaTime);
	void Draw() const;
	~Level();

private:
	GameObject* m_KnightPtr{ nullptr };

	void Start();
};