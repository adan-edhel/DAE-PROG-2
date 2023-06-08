#pragma once

class GameSettings
{
public:
	inline static Vector2 s_ScreenSize{1280.f, 800.f};
	inline static Vector2 s_ScreenCenter{ s_ScreenSize.x / 2, s_ScreenSize.y / 2 };

	inline static float s_MusicVolume{ 10 };
	inline static float s_SoundVolume{ 10 };
};