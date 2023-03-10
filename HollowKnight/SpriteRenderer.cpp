#include "pch.h"
#include <iostream>
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	SpriteRenderer::SpriteRenderer(const std::string& spritePath, const int& rows, const int& columns) :
		m_Sprite{ new Texture(spritePath) },
		m_Rows{rows},
		m_Columns{columns}
	{
	}

	SpriteRenderer::SpriteRenderer(const std::string& spritePath) :
		SpriteRenderer(spritePath, 1, 1) {}

	void SpriteRenderer::Draw() const
	{
		Rectf sliceRect{};
		sliceRect.width = m_Sprite->GetWidth() / float(m_Rows);
		sliceRect.height = m_Sprite->GetHeight() / float(m_Columns);
		sliceRect.left = 0;
		sliceRect.bottom = sliceRect.height;

		const Point2f drawPos{ m_Transform->position.x - sliceRect.width / 2, m_Transform->position.y };

		m_Sprite->Draw(drawPos, sliceRect);
	}

	bool SpriteRenderer::IsFlipped() const { return m_isFlipped; }

	Vector2 SpriteRenderer::Bounds() const
	{
		if (m_Sprite != nullptr)
		{
			return Vector2(m_Sprite->GetWidth(), m_Sprite->GetHeight());
		}
		std::cout << ">>Warning<< No sprite has been loaded.\n";
		return Vector2{};
	}

	const Texture* SpriteRenderer::GetSprite() const { return m_Sprite; }

	SpriteRenderer::~SpriteRenderer()
	{
		delete m_Sprite;
	}
}
