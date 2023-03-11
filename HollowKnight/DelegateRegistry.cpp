#include "pch.h"
#include "DelegateRegistry.h"

// Rendering
Delegate<> DelegateRegistry::drawBackground;
Delegate<> DelegateRegistry::drawPlayground;
Delegate<> DelegateRegistry::drawForeground;
Delegate<> DelegateRegistry::drawUI;

// Updating
Delegate<const float&> DelegateRegistry::regularUpdate;
Delegate<const float&> DelegateRegistry::fixedUpdate;

// User Inputs
Delegate<const SDL_KeyboardEvent&> DelegateRegistry::onKeyDown;
Delegate<const SDL_KeyboardEvent&> DelegateRegistry::onKeyUp;
Delegate<const SDL_MouseMotionEvent&> DelegateRegistry::onMouseMoved;
Delegate<const SDL_MouseButtonEvent&> DelegateRegistry::onMouseDown;
Delegate<const SDL_MouseButtonEvent&> DelegateRegistry::onMouseUp;

// Functions
void DelegateRegistry::CleanUpDelegates()
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