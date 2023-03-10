#include "pch.h"
#include "Global.h"

// Rendering
Delegate<> Global::DrawBackground;
Delegate<> Global::DrawPlayground;
Delegate<> Global::DrawForeground;
Delegate<> Global::DrawUserInterface;

// Updating
Delegate<const float&> Global::UpdateGameObjects;

// User Inputs
Delegate<const SDL_KeyboardEvent&> Global::OnKeyDown;
Delegate<const SDL_KeyboardEvent&> Global::OnKeyUp;
Delegate<const SDL_MouseMotionEvent&> Global::OnMouseMoved;
Delegate<const SDL_MouseButtonEvent&> Global::OnMouseDown;
Delegate<const SDL_MouseButtonEvent&> Global::OnMouseUp;

// Functions
void Global::CleanUpDelegates()
{
	DrawBackground.DisconnectAll();
	DrawPlayground.DisconnectAll();
	DrawForeground.DisconnectAll();
	DrawUserInterface.DisconnectAll();

	UpdateGameObjects.DisconnectAll();

	OnKeyDown.DisconnectAll();
	OnKeyUp.DisconnectAll();
	OnMouseMoved.DisconnectAll();
	OnMouseDown.DisconnectAll();
	OnMouseUp.DisconnectAll();
}