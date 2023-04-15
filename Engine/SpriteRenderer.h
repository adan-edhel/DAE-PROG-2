#pragma once
#include "Component.h"
#include "IDrawable.h"

#include "Vector2.h"
#include "Texture.h"

class SpriteRenderer final : public Component, public IDrawable
{
public:
	bool m_FlipX{ false };
	bool m_FlipY{ false };

	SpriteRenderer(const Texture* sprite = nullptr, const int& rows = 1, const int& cols = 1);
	~SpriteRenderer() override = default;

	void AssignSprite(const Texture* sprite);
	void Draw() const override;

	[[nodiscard]] Rectf GetBounds() const;
	[[nodiscard]] const Texture* GetSprite() const;

private:
	const Texture* m_SpritePtr{nullptr};

	const int m_Rows;
	const int m_Columns;

	void DebugDraw() const override;
};