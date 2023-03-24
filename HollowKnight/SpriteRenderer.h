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

	SpriteRenderer(const std::string& spritePath, const int& rows, const int& columns);
	SpriteRenderer(const std::string& spritePath = "default_circle.png");

	void Draw() const override;

	Vector2 Bounds() const;
	const Texture* GetSprite() const;

	~SpriteRenderer() override;

private:
	Texture* m_pSprite;

	const int m_Rows;
	const int m_Columns;
};