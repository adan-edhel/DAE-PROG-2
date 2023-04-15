#pragma once
#include "Component.h"
#include "IUpdatable.h"

#include "Transform.h"
#include "GameObject.h"

class Behavior : public Component, public IUpdatable
{
protected:
	Behavior();
	virtual ~Behavior() override;

	virtual void Update(const float& deltaTime) override;
	virtual void OnDestroy();
};