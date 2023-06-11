#include "pch.h"
#include "Game.h"

// Libraries
#include "SpriteLibrary.h"
#include "AnimLibrary.h"

#include "SceneManager.h"
#include "GameSettings.h"
#include "IInputEvent.h"
#include "Camera.h"
#include "Level.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Start();
}

void Game::Start( )
{
	m_MenuPtr = new Menu();

	// Setup camera
	m_CameraPtr = new GameObject();
	m_CameraPtr->AddComponent(new Camera(GameSettings::s_ScreenSize));

	m_KingsPassPtr = new Level("King's Pass");
}

void Game::End( )
{
	delete m_CameraPtr;

	delete m_KingsPassPtr;
	delete m_MenuPtr;
}

void Game::Update(const float& deltaTime )
{
	if (SceneManager::GetCurrentScene() == Scene::Game)
	{
		m_KingsPassPtr->Update(deltaTime);
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
		m_MenuPtr->Draw();
		break;
	case Scene::Game:
		m_KingsPassPtr->Draw();
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
			SceneManager::SetScene(Scene::Menu);
			SceneManager::ReloadLevel(m_KingsPassPtr, "King's Pass");
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
		m_MenuPtr->HighlightButton(e.x, e.y);
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
		m_MenuPtr->SelectButton();
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