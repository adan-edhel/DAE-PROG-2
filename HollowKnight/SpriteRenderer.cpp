#include "pch.h"
#include <iostream>

#include "Transform.h"
#include "SpriteRenderer.h"

#include "AmrothUtils.h"
#include "SpriteLibrary.h"

SpriteRenderer::SpriteRenderer(const std::string& spritePath, const int& rows, const int& columns) :
	Component("SpriteRenderer"),
	IDrawable(s_MidLayer),
	m_SpritePtr{ SpriteLibrary::GetSprite(SpriteLibrary::Type::Default)},
	m_Rows{ rows },
	m_Columns{ columns }
{
}

SpriteRenderer::SpriteRenderer(const std::string& spritePath) :
	SpriteRenderer(spritePath, 1, 1) {}

void SpriteRenderer::Draw() const
{
	Rectf sliceRect{};
	sliceRect.width		= m_SpritePtr->GetWidth()  / float(m_Rows);
	sliceRect.height	= m_SpritePtr->GetHeight() / float(m_Columns);
	sliceRect.left		= 0;
	sliceRect.bottom	= sliceRect.height;

	Rectf drawRect{};
	drawRect.left	= m_Transform->position.x - sliceRect.width / 2;
	drawRect.bottom = m_Transform->position.y;
	drawRect.width	= sliceRect.width  * float(m_FlipX ? -1 : 1);
	drawRect.height = sliceRect.height * float(m_FlipY ? -1 : 1);

	m_SpritePtr->Draw(drawRect, sliceRect);
}

Vector2 SpriteRenderer::Bounds() const
{
	if (m_SpritePtr != nullptr)
	{
		return Vector2(m_SpritePtr->GetWidth(), m_SpritePtr->GetHeight());
	}
	Print(">>Warning<< No sprite has been loaded.\n", TextColor::Red);
	return Vector2{};
}

const Texture* SpriteRenderer::GetSprite() const
{
	return m_SpritePtr;
}