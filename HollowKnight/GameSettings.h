#pragma once
#include "Object.h"

class GameSettings
{
public:
	//TODO: disable
	inline static bool s_DebugMode{ true };

	inline static Vector2 s_Screen{1280.f, 800.f};

	inline static float s_MusicVolume{ 10 };
	inline static float s_SoundVolume{ 10 };
};
