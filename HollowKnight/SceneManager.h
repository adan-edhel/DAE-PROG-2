#pragma once

class Level;

enum class Scene
{
	Menu,
	Game
};

class SceneManager final
{
public:
	// Returns the current scene
	static Scene GetCurrentScene();

	// Sets new active scene
	static void SetScene(Scene scene);

	// Reloads level with a fresh instance
	static void ReloadLevel(Level*& level, const std::string& name);

private:
	// Dynamic state of the game
	inline static Scene s_ActiveScene{Scene::Menu};
};