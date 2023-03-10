#pragma once
#include "Transform.h"
#include "Texture.h"

namespace AmrothFramework
{
	class SpriteRenderer : public IComponent
	{
	public:
		SpriteRenderer(const std::string& spritePath = "default_sprite.png");
		void Draw() const;
		void Update(const float& deltaTime) override;
		bool IsFlipped() const;
		Vector2 Bounds() const;
		~SpriteRenderer() override;

	private:
		Texture* m_Sprite;
		bool m_isFlipped{ false };
	};

}