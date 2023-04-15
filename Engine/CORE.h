#pragma once

enum class GameState
{
	Menu,
	Settings,
	Game
};

class CORE
{
public:
	inline static bool s_DebugMode{ true };
	inline static Rectf s_GameArea{};
};