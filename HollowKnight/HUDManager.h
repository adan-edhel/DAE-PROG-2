#pragma once
#include "IDrawable.h"
#include "SpriteLibrary.h"

#include <array>

#include "Knight.h"

class HUDManager final : IUpdatable, IDrawable
{
	struct AncientMask
	{
	private:
		Texture* m_Texture{ SpriteLibrary::GetSprite(Sprite::AncientMask) };
		const float m_Scale{ 0.15f };

	public:
		bool m_Active{ true };

		void Draw(const Vector2& position) const
		{
			Rectf sliceRect{};
			sliceRect.width = m_Texture->GetWidth() / 2;
			sliceRect.height= m_Texture->GetHeight();
			sliceRect.left	= !m_Active ? 0 : sliceRect.width;

			Rectf drawRect{};
			drawRect.width	= sliceRect.width * m_Scale;
			drawRect.height = sliceRect.height * m_Scale;
			drawRect.left	= position.x - drawRect.width / 2;
			drawRect.bottom = position.y - drawRect.height / 2;

			m_Texture->Draw(drawRect, sliceRect);
		}
	};

public:
	static HUDManager& GetInstance()
	{
		static HUDManager instance;
		return instance;
	}

	HUDManager();

	void UpdatePlayerPosition(const Vector2& position);
	void UpdatePlayerHealth(const int& health, const int& maxHealth);

private:
	// Text settings
	int m_FontSize{ 30 };
	Color4f m_FontColor{ 0.5f, 0.5f, 0.5f, 1 };
	std::string m_Font{ SpriteLibrary::GetFont(Font::TrajanPro) };

	//Debug values
	Vector2 m_PlayerPosition{};
	int m_PlayerMaxHealth{};
	int m_PlayerHealth{};

	// Ancient Masks
	std::array<AncientMask, 5> m_AncientMasks{};
	const Vector2 m_MasksPositionsOrigin{100, 700};
	const float m_MasksOffset{50};

	void Update(const float& deltaTime) override;
	void UIDraw() const override;

	void DrawString(const std::string& text, const Vector2 position = Vector2{}) const;
};

