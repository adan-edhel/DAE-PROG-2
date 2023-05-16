#include "pch.h"
#include "Game.h"

#include "SpriteLibrary.h"
#include "GameSettings.h"
#include "AnimLibrary.h"
#include "Camera.h"

#include "IInputEvent.h"

#include "Level.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Start();
}

void Game::Start( )
{
	SpriteLibrary::Setup();
	AnimLibrary::Setup();

	// Set game state
	m_State = m_BeginState;

	// Setup camera
	m_CameraPtr = new GameObject();
	m_CameraPtr->AddComponent(new Camera(GameSettings::s_Screen));

	if (m_State == m_BeginState)
	{
		m_KingsPassPtr = new Level("King's Pass");
	}
}

void Game::End( )
{
	delete Camera::m_MainPtr->m_GameObject;

	delete m_KingsPassPtr;

	AnimLibrary::Cleanup();
	SpriteLibrary::Cleanup();
}

void Game::Update(const float& deltaTime )
{
	m_KingsPassPtr->Update(deltaTime);
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
	m_KingsPassPtr->Draw();
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