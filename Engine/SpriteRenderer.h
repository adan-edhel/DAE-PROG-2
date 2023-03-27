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

	SpriteRenderer(const std::string& spritePath = "");
	~SpriteRenderer() override;

	void AssignSprite(const Texture* sprite);
	void Draw() const override;

	[[nodiscard]] Vector2 Bounds() const;
	[[nodiscard]] const Texture* GetSprite() const;

private:
	const Texture* m_DefaultSpritePtr;
	const Texture* m_SpritePtr;

	const int m_Rows;
	const int m_Columns;
};