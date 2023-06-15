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

	Transform() = default;
	~Transform() override = default;
	Transform(const Transform& other) = delete;	// copy constructor
	Transform(Transform&& other) noexcept = delete;	// move constructor
	Transform& operator=(const Transform& other) = delete;	// copy operator
	Transform& operator=(Transform&& other) noexcept = delete;	// move operator

	void Translate(const float& x, const float& y);
	void Translate(const Vector2& displacement);

private:
	void DebugDraw() const override;
};
