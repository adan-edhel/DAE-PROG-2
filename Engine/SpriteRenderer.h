#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "Texture.h"

class Animator;

class SpriteRenderer final : public Component, IDrawable
{
public:
	bool m_FlipX{ false };
	bool m_FlipY{ false };

	SpriteRenderer(Texture* sprite = nullptr, const int& rows = 1, const int& cols = 1);
	~SpriteRenderer() override = default;

	void SetLayer(const int& layer) override;
	int GetLayer() const override;

	void AssignSprite(Texture* sprite);

	[[nodiscard]] Rectf GetBounds() const;

private:
	friend Animator;

	Texture* m_SpritePtr;

	Rectf m_Slice{};
	int m_Rows;
	int m_Columns;

	void Draw() const override;
	void Slice(const Rectf& slice);
	void DebugDraw() const override;
};