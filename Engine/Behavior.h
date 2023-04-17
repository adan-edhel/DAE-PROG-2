#pragma once
#include "Component.h"

// Include for derived classes
#include "Transform.h"
#include "GameObject.h"

class Behavior : public Component
{
protected:
	Behavior();
	virtual ~Behavior() override;
	virtual void OnDestroy();
};