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
	GameObject* m_CameraPtr;
	GameObject* m_KnightPtr;

	void Start();
};