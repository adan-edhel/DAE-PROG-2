#pragma once

enum class Scene
{
	Menu,
	Game
};

class SceneManager final
{
public:
	static Scene GetCurrentScene();
	static void SetScene(Scene scene);

private:
	// Dynamic state of the game
	inline static Scene s_Scene{Scene::Game};
};