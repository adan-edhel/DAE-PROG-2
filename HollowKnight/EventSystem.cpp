#include "pch.h"
#include "EventSystem.h"

// Rendering
Event<> EventSystem::drawBackground;
Event<> EventSystem::drawPlayground;
Event<> EventSystem::drawForeground;
Event<> EventSystem::drawUI;

// Updating
Event<const float&> EventSystem::regularUpdate;
Event<const float&> EventSystem::fixedUpdate;

// User Inputs
Event<const SDL_KeyboardEvent&> EventSystem::onKeyDown;
Event<const SDL_KeyboardEvent&> EventSystem::onKeyUp;
Event<const SDL_MouseMotionEvent&> EventSystem::onMouseMoved;
Event<const SDL_MouseButtonEvent&> EventSystem::onMouseDown;
Event<const SDL_MouseButtonEvent&> EventSystem::onMouseUp;

// Functions
void EventSystem::CleanUpDelegates()
{
	drawBackground.DisconnectAll();
	drawPlayground.DisconnectAll();
	drawForeground.DisconnectAll();
	drawUI.DisconnectAll();

	regularUpdate.DisconnectAll();
	fixedUpdate.DisconnectAll();

	onKeyDown.DisconnectAll();
	onKeyUp.DisconnectAll();
	onMouseMoved.DisconnectAll();
	onMouseDown.DisconnectAll();
	onMouseUp.DisconnectAll();
}