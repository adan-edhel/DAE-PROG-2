#pragma once
#include "Component.h"

class Behavior : public Component
{
protected:
	Behavior();
	virtual ~Behavior() override = default;
};

