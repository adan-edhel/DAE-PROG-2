#pragma once
#include "Delegate.h"

class Global final
{
public:
	// Rendering
	static Delegate<> DrawBackground;
	static Delegate<> DrawPlayground;
	static Delegate<> DrawForeground;
	static Delegate<> DrawUserInterface;

	// Updating
	static Delegate<const float&> UpdateObjects;

	// User Inputs
	static Delegate<const SDL_KeyboardEvent&> OnKeyDown;
	static Delegate<const SDL_KeyboardEvent&> OnKeyUp;
	static Delegate<const SDL_MouseMotionEvent&> OnMouseMoved;
	static Delegate<const SDL_MouseButtonEvent&> OnMouseDown;
	static Delegate<const SDL_MouseButtonEvent&> OnMouseUp;

	// Functions
	static void CleanUpDelegates();
};