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
	inline static bool s_DebugMode{ false };
	inline static Rectf s_GameArea{};
};