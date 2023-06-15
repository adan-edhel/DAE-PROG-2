#pragma once

class Menu;
class Level;

enum class Scene
{
	Menu,
	Game
};

class SceneManager final
{
public:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager& other) = delete;					// copy constructor
	SceneManager(SceneManager&& other) noexcept = delete;				// move constructor
	SceneManager& operator=(const SceneManager& other) = delete;		// copy operator
	SceneManager& operator=(SceneManager&& other) noexcept = delete;	// move operator

	// Returns the current scene
	static Scene GetCurrentScene();

	// Return scene reference
	template<typename T>
	static T* GetScene()
	{
		if constexpr (std::is_same_v<T, Level>)
		{
			return s_KingsPassPtr;
		}
		else if constexpr (std::is_same_v<T, Menu>)
		{
			return s_MenuPtr;
		}
		else
		{
			return nullptr;
		}
	}

	// Reloads level with a fresh instance
	static void LoadScene(const Scene& scene);
	static void Quit();

private:
	// Dynamic state of the game
	inline static Scene s_ActiveScene{Scene::Menu};
	inline static Level* s_KingsPassPtr{};
	inline static Menu* s_MenuPtr{};

	static void UnloadLevels();
};