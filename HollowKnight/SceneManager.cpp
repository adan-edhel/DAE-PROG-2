#include "pch.h"
#include "SceneManager.h"

Scene SceneManager::GetCurrentScene()
{
	return s_Scene;
}

void SceneManager::SetScene(Scene scene)
{
	s_Scene = scene;
}
