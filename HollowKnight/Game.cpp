#include "pch.h"
#include "Game.h"

#include <SoundEffect.h>
#include <IInputEvent.h>
#include <Camera.h>

#include "CORE.h"
#include "SceneManager.h"
#include "GameSettings.h"
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
	IInputEvent::Invoke(&IInputEvent::OnKeyDown, e);

	switch (e.keysym.sym)
	{
	case SDLK_F1:			// TOGGLE DEBUG
		CORE::s_DebugMode = !CORE::s_DebugMode;
		break;
	case SDLK_F5:			// Clear Console
		ClearConsole();
		break;
	case SDLK_i:			// Print Controls
		Print("___________________________________\n");
		Print("|             CONTROLS            |\n");
		Print("|_________________________________|\n");
		Print("| Ones with '*' are bonus goals   |\n");
		Print("| and may possibly be unfinished. |\n");
		Print("|_________________________________|\n");
		Print("| Left Arrow     | Move Left      |\n");
		Print("|_________________________________|\n");
		Print("| Right Arrow    | Move Right     |\n");
		Print("|_________________________________|\n");
		Print("| Z              | Jump           |\n");
		Print("|_________________________________|\n");
		Print("| X              | Attack         |\n");
		Print("|_________________________________|\n");
		Print("| C              | Dash           |\n");
		Print("|_________________________________|\n");
		Print("| *A             | *Focus/Heal    |\n");
		Print("|_________________________________|\n");
		Print("| Escape         | Quit to menu   |\n");
		Print("|_________________________________|\n");
		Print("| F1             | Debug Info     |\n");
		Print("|_________________________________|\n");
		Print("| F2             | Print Position |\n");
		Print("|_________________________________|\n");
		Print("| F3             | Debug Movement |\n");
		Print("|_________________________________|\n");
		Print("| F5             | Clear Console  |\n");
		Print("|_________________________________|\n");
		break;
	case SDLK_ESCAPE:			// Exit
		switch (SceneManager::GetCurrentScene())
		{
		case Scene::Menu:
			SceneManager::Quit();
			break;
		case Scene::Game:
			SceneManager::LoadScene(Scene::Menu);
			break;
		}
		break;
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
	IInputEvent::Invoke(&IInputEvent::OnMouseMotion, e);
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	IInputEvent::Invoke(&IInputEvent::OnMouseDown, e);
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