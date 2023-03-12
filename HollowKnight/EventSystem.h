#pragma once
#include "Delegate.h"

class EventSystem final
{
public:
	// Rendering
	static Delegate<> drawBackground;
	static Delegate<> drawPlayground;
	static Delegate<> drawForeground;
	static Delegate<> drawUI;

	// Updating
	static Delegate<const float&> regularUpdate;
	static Delegate<const float&> fixedUpdate; //Not implemented

	// User Inputs
	static Delegate<const SDL_KeyboardEvent&> onKeyDown;
	static Delegate<const SDL_KeyboardEvent&> onKeyUp;
	static Delegate<const SDL_MouseMotionEvent&> onMouseMoved;
	static Delegate<const SDL_MouseButtonEvent&> onMouseDown;
	static Delegate<const SDL_MouseButtonEvent&> onMouseUp;

	// Functions
	static void CleanUpDelegates();
};