#pragma once
#include "InputActions.h"
#include "GameObject.h"

class InputHandler
{
public:
	InputHandler(GameObject& player);
	~InputHandler();

private:
	void OnKeyDown(const SDL_KeyboardEvent& e);
	void OnKeyUp(const SDL_KeyboardEvent& e);
	void OnMouseMoved(const SDL_MouseMotionEvent& e);
	void OnMouseDown(const SDL_MouseButtonEvent& e);
	void OnMouseUp(const SDL_MouseButtonEvent& e);
};