#include "pch.h"
#include <iostream>
#include "Transform.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string& spritePath, const int& rows, const int& columns) :
	m_pSprite{ new Texture(spritePath) },
	m_Rows{ rows },
	m_Columns{ columns }
{
}

SpriteRenderer::SpriteRenderer(const std::string& spritePath) :
	SpriteRenderer(spritePath, 1, 1) {}

void SpriteRenderer::Draw() const
{
	if (!m_pIsActive) return;

	Rectf sliceRect{};
	sliceRect.width = m_pSprite->GetWidth() / float(m_Rows);
	sliceRect.height = m_pSprite->GetHeight() / float(m_Columns);
	sliceRect.left = 0;
	sliceRect.bottom = sliceRect.height;

	const Point2f drawPos{ m_pTransform->position.x - sliceRect.width / 2, m_pTransform->position.y };

	m_pSprite->Draw(drawPos, sliceRect);
}

bool SpriteRenderer::IsFlipped() const { return m_isFlipped; }

Vector2 SpriteRenderer::Bounds() const
{
	if (m_pSprite != nullptr)
	{
		return Vector2(m_pSprite->GetWidth(), m_pSprite->GetHeight());
	}
	std::cout << ">>Warning<< No sprite has been loaded.\n";
	return Vector2{};
}

const Texture* SpriteRenderer::GetSprite() const { return m_pSprite; }

SpriteRenderer::~SpriteRenderer()
{
	delete m_pSprite;
}
