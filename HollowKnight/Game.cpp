#include "pch.h"
#include "Game.h"
#include "EventSystem.h"
#include "Rigidbody2D.h"

#include "Knight.h"
#include "Level.h"

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
	EventSystem::CleanUpDelegates();

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
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	EventSystem::onKeyDown.Invoke(e);

	using AmrothFramework::Rigidbody2D;
	Rigidbody2D* pRigidbody{ m_pKnight->m_GameObject.GetComponent<Rigidbody2D>() };

	switch (e.keysym.sym)
	{
	case SDLK_w:			// UP
		break;
	case SDLK_s:			// DOWN
		break;
	case SDLK_a:			// LEFT
		pRigidbody->AddForce(Vector2(-15,0));
		break;
	case SDLK_d:			// RIGHT
		pRigidbody->AddForce(Vector2(15, 0));
		break;
	case SDLK_SPACE:		// JUMP
		pRigidbody->AddForce(Vector2(0, 5));
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		m_pKnight->m_GameObject.SetActive(!m_pKnight->m_GameObject.isActive());
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	EventSystem::onKeyUp.Invoke(e);

	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

#pragma endregion
#pragma region Mouse

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	mousePos = Vector2(e.x, e.y);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	m_pKnight->m_GameObject.transform.position = mousePos;

	switch (e.type)
	{
	case SDL_MOUSEBUTTONUP:
		std::cout << "Button up\n";
		break;
	}

	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "Button down\n";
		break;
	}

	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

#pragma endregion
#pragma endregion

Game::~Game()
{
	End();
}