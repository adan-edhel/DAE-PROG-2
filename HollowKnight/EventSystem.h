#pragma once
#include "Event.h"

class EventSystem final
{
public:
	// Rendering
	static Event<> drawBackground;
	static Event<> drawPlayground;
	static Event<> drawForeground;
	static Event<> drawUI;

	// Updating
	static Event<const float&> regularUpdate;
	static Event<const float&> fixedUpdate; //Not implemented

	// User Inputs
	static Event<const SDL_KeyboardEvent&> onKeyDown;
	static Event<const SDL_KeyboardEvent&> onKeyUp;
	static Event<const SDL_MouseMotionEvent&> onMouseMoved;
	static Event<const SDL_MouseButtonEvent&> onMouseDown;
	static Event<const SDL_MouseButtonEvent&> onMouseUp;

	// Functions
	static void CleanUp();
};