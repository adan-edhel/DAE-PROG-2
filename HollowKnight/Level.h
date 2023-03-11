#pragma once
#include "Knight.h"

class Level
{
public:
	Knight* m_Knight;

	Level(Knight& knight);
	void Setup();
	~Level();
};

