#pragma once
#include "BaseGame.h"
#include <CORE.h>

#include "Menu.h"

class GameObject;
class Knight;
class Level;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game() override;

	void Update( const float& deltaTime ) override;
	void Draw( ) const override;

#pragma region Input
	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
#pragma endregion
private:
	// Begin state of the game
	const GameState m_BeginState{ GameState::Game };

	// Dynamic state of the game
	GameState m_State{};

	// Menu
	Menu* m_MenuPtr;

	// Level
	Level* m_KingsPassPtr{};

	// Camera
	GameObject* m_CameraPtr;

	// FUNCTIONS
	void Start();
	void End( );
	void ClearBackground( ) const;
};
