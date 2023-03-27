#pragma once
#include "Component.h"

#include "Vector2.h"

class Transform final : public Component
{
public:
	Vector2 position{};
	Vector2 rotation{};
	Vector2 scale{};

	Transform();
	void Translate(const Vector2& displacement);
	void Translate(const float& x, const float& y);
	~Transform() override = default;
};