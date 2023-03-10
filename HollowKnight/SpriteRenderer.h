#pragma once
#include "Transform.h"
#include "Texture.h"

namespace AmrothFramework
{
	class SpriteRenderer : public IComponent
	{
	public:
		SpriteRenderer(const std::string& spritePath, const int& rows, const int& columns);
		SpriteRenderer(const std::string& spritePath = "default_sprite.png");

		void Draw() const override;

		bool IsFlipped() const;
		Vector2 Bounds() const;
		const Texture* GetSprite() const;

		~SpriteRenderer() override;

	private:
		Texture* m_Sprite;
		bool m_isFlipped{ false };

		const int m_Rows;
		const int m_Columns;
	};

}