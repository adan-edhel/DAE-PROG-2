#include "pch.h"
#include "DelegateRegistry.h"
#include "InputHandler.h"

InputHandler::InputHandler(GameObject& player)
{
	DelegateRegistry::onKeyDown.Connect(this, &InputHandler::OnKeyDown);
	DelegateRegistry::onKeyUp.Connect(this, &InputHandler::OnKeyUp);
	DelegateRegistry::onMouseMoved.Connect(this, &InputHandler::OnMouseMoved);
	DelegateRegistry::onMouseDown.Connect(this, &InputHandler::OnMouseDown);
	DelegateRegistry::onMouseUp.Connect(this, &InputHandler::OnMouseUp);
}

void InputHandler::OnKeyDown(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:			// UP
		break;
	case SDLK_s:			// DOWN
		break;
	case SDLK_a:			// LEFT
		Walk();
		break;
	case SDLK_d:			// RIGHT
		Walk();
		break;
	case SDLK_SPACE:		// JUMP
		Jump();
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	default:
		break;
	}
}

void InputHandler::OnKeyUp(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:			// UP
		break;
	case SDLK_s:			// DOWN
		break;
	case SDLK_a:			// LEFT
		break;
	case SDLK_d:			// RIGHT
		break;
	case SDLK_SPACE:		// JUMP
		CutJump();
		break;
	case SDLK_RSHIFT:		// ATTACK
		break;
	case SDLK_LSHIFT:		// DASH
		break;
	case SDLK_e:			// FOCUS / CAST
		break;
	case SDLK_r:			// DREAM NAIL
		break;
	case SDLK_ESCAPE:		// MENU
		break;
	default:
		break;
	}
}

void InputHandler::OnMouseMoved(const SDL_MouseMotionEvent& e)
{
	m_MousePos = Vector2(e.x, e.y);
}

void InputHandler::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	
}

void InputHandler::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	
}

InputHandler::~InputHandler()
{
	DelegateRegistry::onKeyDown.Disconnect(this, &InputHandler::OnKeyDown);
	DelegateRegistry::onKeyUp.Disconnect(this, &InputHandler::OnKeyUp);
	DelegateRegistry::onMouseMoved.Disconnect(this, &InputHandler::OnMouseMoved);
	DelegateRegistry::onMouseDown.Disconnect(this, &InputHandler::OnMouseDown);
	DelegateRegistry::onMouseUp.Disconnect(this, &InputHandler::OnMouseUp);
}