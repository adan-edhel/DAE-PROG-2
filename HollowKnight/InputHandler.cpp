#include "pch.h"
#include "Global.h"
#include "InputHandler.h"

InputHandler::InputHandler(GameObject& player)
{
	Global::OnKeyDown.Connect(this, &InputHandler::OnKeyDown);
	Global::OnKeyUp.Connect(this, &InputHandler::OnKeyUp);
	Global::OnMouseMoved.Connect(this, &InputHandler::OnMouseMoved);
	Global::OnMouseDown.Connect(this, &InputHandler::OnMouseDown);
	Global::OnMouseUp.Connect(this, &InputHandler::OnMouseUp);
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
	Global::OnKeyDown.Disconnect(this, &InputHandler::OnKeyDown);
	Global::OnKeyUp.Disconnect(this, &InputHandler::OnKeyUp);
	Global::OnMouseMoved.Disconnect(this, &InputHandler::OnMouseMoved);
	Global::OnMouseDown.Disconnect(this, &InputHandler::OnMouseDown);
	Global::OnMouseUp.Disconnect(this, &InputHandler::OnMouseUp);
}