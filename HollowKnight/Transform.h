#pragma once
#include "IComponent.h"
#include "Vector2.h"

class Transform : public IComponent
{
public:
	Point2f position{};
	Vector2 rotation{};
	Vector2 scale{};

	void Update(float deltaTime) override;
};

