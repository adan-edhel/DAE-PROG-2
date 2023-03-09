#pragma once
#include "IComponent.h"
#include "Texture.h"
#include "Vector2.h"

namespace AmrothFramework
{
	class Transform;

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