#pragma once
#include "Component.h"
#include "IDrawable.h"

#include "Vector2.h"

class Transform final : public Component, IDrawable
{
public:
	Vector2 position{};
	Vector2 rotation{};
	Vector2 scale{1, 1};

	Transform();
	void Translate(const float& x, const float& y);
	void Translate(const Vector2& displacement);

private:
	~Transform() override = default;
	void DebugDraw() const override;
};
