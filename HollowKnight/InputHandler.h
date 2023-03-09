#pragma once
#include "InputActions.h"
#include "Object.h"

using AmrothFramework::Object;

class InputHandler : public InputActions
{
public:
	InputHandler(Object& player);
	~InputHandler() override;

private:
	void OnKeyDown(const SDL_KeyboardEvent& e);
	void OnKeyUp(const SDL_KeyboardEvent& e);
	void OnMouseMoved(const SDL_MouseMotionEvent& e);
	void OnMouseDown(const SDL_MouseButtonEvent& e);
	void OnMouseUp(const SDL_MouseButtonEvent& e);
};