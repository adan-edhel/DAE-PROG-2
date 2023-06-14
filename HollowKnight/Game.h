#pragma once
#include "SpriteLibrary.h"
#include "AudioLibrary.h"
#include "AnimLibrary.h"
#include "BaseGame.h"
#include "Menu.h"
#include "SceneManager.h"

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
	// Asset Libraries
	AudioLibrary m_AudioLibrary{};
	SpriteLibrary m_SpriteLibrary{};
	AnimLibrary m_AnimationLibrary{}; // Load after SpriteLibrary!

	SceneManager m_SceneManager{};
	GameObject m_Camera{};

	// FUNCTIONS
	void Start();
	void End( );
	void ClearBackground( ) const;
};
