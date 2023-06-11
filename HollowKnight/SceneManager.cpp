#include "pch.h"
#include "SceneManager.h"

#include "Menu.h"
#include "Level.h"
#include "SoundEffect.h"

SceneManager::SceneManager()
{
	LoadScene(Scene::Menu);
}

SceneManager::~SceneManager()
{
	UnloadLevels();
}

Scene SceneManager::GetCurrentScene()
{
	return s_ActiveScene;
}

void SceneManager::LoadScene(const Scene& scene)
{
	s_ActiveScene = scene;

	SoundEffect::StopAll();
	UnloadLevels();

	switch (s_ActiveScene)
	{
	case Scene::Menu:
		s_MenuPtr = new Menu();
		break;
	case Scene::Game:
		s_KingsPassPtr = new Level("King's Pass");
		break;
	}
}

void SceneManager::UnloadLevels()
{
	delete s_KingsPassPtr;
	s_KingsPassPtr = nullptr;

	delete s_MenuPtr;
	s_MenuPtr = nullptr;
}
