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
	Cleanup();
}

Scene SceneManager::GetCurrentScene()
{
	return s_ActiveScene;
}

void SceneManager::LoadScene(const Scene& scene)
{
	s_ActiveScene = scene;

	SoundEffect::StopAll();
	Cleanup();

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

void SceneManager::Quit()
{
	Print("###################################\n");
	Print("#     THANK YOU FOR PLAYING!      #\n");
	Print("###################################\n");
	Print("#          HOLLOW KNIGHT          #\n");
	Print("###################################\n");
	Print("#        (Re)Made by Mort         #\n");
	Print("###################################\n");
	SDL_Event quit{};
	quit.type = SDL_QUIT;
	SDL_PushEvent(&quit);
}

void SceneManager::Cleanup()
{
	delete s_KingsPassPtr;
	s_KingsPassPtr = nullptr;

	delete s_MenuPtr;
	s_MenuPtr = nullptr;
}
