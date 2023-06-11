#include "pch.h"
#include "Game.h"

#include "SceneManager.h"
#include "GameSettings.h"
#include <SoundEffect.h>
#include "IInputEvent.h"
#include "Camera.h"
#include "Level.h"

Game::Game(const Window& window)
	:BaseGame{ window }
{
	Start();
}

void Game::Start( )
{
	// Setup camera
	m_Camera.AddComponent(new Camera(GameSettings::s_ScreenSize));
}

void Game::End( )
{

}

void Game::Update(const float& deltaTime )
{
	if (SceneManager::GetCurrentScene() == Scene::Game)
	{
		SceneManager::GetScene<Level>()->Update(deltaTime);
	}

	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );

	switch (SceneManager::GetCurrentScene())
	{
	case Scene::Menu:
		SceneManager::GetScene<Menu>()->Draw();
		break;
	case Scene::Game:
		SceneManager::GetScene<Level>()->Draw();
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); // default: blue(0.3)
	glClear( GL_COLOR_BUFFER_BIT );
}

#pragma region Input Events
#pragma region Keyboard
void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (SceneManager::GetCurrentScene() == Scene::Game)
	{
		if (e.keysym.sym == SDLK_ESCAPE)
		{
			SceneManager::LoadScene(Scene::Menu);
			return;
		}
		IInputEvent::Invoke(&IInputEvent::OnKeyDown, e);
	}
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	IInputEvent::Invoke(&IInputEvent::OnKeyUp, e);
}
#pragma endregion
#pragma region Mouse
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	if (SceneManager::GetCurrentScene() == Scene::Menu)
	{
		SceneManager::GetScene<Menu>()->HighlightButton(e.x, e.y);
	}
	else
	{
		IInputEvent::Invoke(&IInputEvent::OnMouseMotion, e);
	}
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	if (SceneManager::GetCurrentScene() == Scene::Menu)
	{
		SceneManager::GetScene<Menu>()->SelectButton();
	}
	else
	{
		IInputEvent::Invoke(&IInputEvent::OnMouseDown, e);
	}
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	IInputEvent::Invoke(&IInputEvent::OnMouseUp, e);
}
#pragma endregion
#pragma endregion

Game::~Game()
{
	End();
}