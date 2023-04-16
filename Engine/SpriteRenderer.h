#pragma once
#include "Component.h"
#include "IDrawable.h"

#include "Vector2.h"
#include "Texture.h"

class Animator;

class SpriteRenderer final : public Component, public IDrawable
{
public:
	bool m_FlipX{ false };
	bool m_FlipY{ false };

	SpriteRenderer(Texture* sprite = nullptr, const int& rows = 1, const int& cols = 1);
	~SpriteRenderer() override = default;

	void AssignSprite(Texture* sprite);
	void Draw() const override;

	[[nodiscard]] Rectf GetBounds() const;

private:
	friend Animator;

	Texture* m_SpritePtr;

	Rectf m_Slice{};
	int m_Rows;
	int m_Columns;

	void Slice(const Rectf& slice);
	void DebugDraw() const override;
};