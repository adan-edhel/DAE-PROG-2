#pragma once

class GameObject;

class Level final
{
public:
	Level(const std::string& levelName);
	~Level();

	void Update(const float& deltaTime);
	void Draw() const;

private:
	Texture* levelRef;

	GameObject* m_KnightPtr;
	GameObject* m_LevelVisuals;

	void Start();
};