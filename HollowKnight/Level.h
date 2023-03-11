#pragma once
#include "Knight.h"

class Level
{
public:
	Knight* m_pKnight;

	Level(Knight& knight);
	void Setup();
	~Level();
};

