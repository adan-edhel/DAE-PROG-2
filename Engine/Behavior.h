#pragma once
#include "Component.h"

// Include for derived classes
#include "Transform.h"
#include "GameObject.h"

class Behavior : public Component
{
protected:
	Behavior(const std::string& name = "");
	virtual ~Behavior() override = default;
};