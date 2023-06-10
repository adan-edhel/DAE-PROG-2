#include "pch.h"
#include "Level.h"
#include "SceneManager.h"

Scene SceneManager::GetCurrentScene()
{
	return s_ActiveScene;
}

void SceneManager::SetScene(Scene scene)
{
	s_ActiveScene = scene;
}

void SceneManager::ReloadLevel(Level*& level, const std::string& name)
{
	delete level;
	level = new Level(name);
}
