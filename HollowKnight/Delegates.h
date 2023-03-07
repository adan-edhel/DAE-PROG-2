#pragma once
#include "Delegate.h"

class Delegates
{
public:
	static Delegate<> DrawObjects;
	static Delegate<const float&> UpdateObjects;

	~Delegates();
};

