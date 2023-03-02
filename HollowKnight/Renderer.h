#pragma once
#include "IComponent.h"

class Renderer : public IComponent
{
public:
	void Update(float deltaTime) override;
};

