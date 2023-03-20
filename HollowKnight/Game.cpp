#include "pch.h"
#include "Game.h"

#include "IInputEvent.h"

#include "Level.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Start();
}

void Game::Start( )
{
	m_pKingsPass = new Level("King's Pass");
}

void Game::End( )
{
	delete m_pKingsPass;
	m_pKingsPass = nullptr;
}

void Game::Update(const float& deltaTime )
{
	m_pKingsPass->Update(deltaTime);
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
	m_pKingsPass->Draw();
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