#include "pch.h"
#include "Game.h"
#include "EventSystem.h"
#include "Rigidbody2D.h"

#include "Knight.h"
#include "Level.h"
#include "IEvent.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Start();
}

void Game::Start( )
{
	m_pKnight = new Knight();
	m_pKingsPass = new Level(*m_pKnight);
}

void Game::End( )
{
	EventSystem::CleanUp();

	delete m_pKingsPass;
	delete m_pKnight;
}

void Game::Update( float deltaTime )
{
	EventSystem::regularUpdate.Invoke(deltaTime);

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

	EventSystem::drawBackground.Invoke();
	EventSystem::drawPlayground.Invoke();
	EventSystem::drawForeground.Invoke();
	EventSystem::drawUI.Invoke();
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

#pragma region Input Events
#pragma region Keyboard
void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	IEvent::Invoke(&IEvent::OnKeyDown, e);
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	IEvent::Invoke(&IEvent::OnKeyUp, e);
}
#pragma endregion
#pragma region Mouse
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	IEvent::Invoke(&IEvent::OnMouseMotion, e);
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	IEvent::Invoke(&IEvent::OnMouseDown, e);

}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	IEvent::Invoke(&IEvent::OnMouseUp, e);
}
#pragma endregion
#pragma endregion

Game::~Game()
{
	End();
}