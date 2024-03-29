#include "SpriteRenderer.h"
#include "GameObject.h"

#include "AmrothUtils.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(Texture* sprite, const int& rows, const int& cols) :
	Component("SpriteRenderer"),
	IDrawable(s_MidLayer),
	m_SpritePtr{ sprite },
	m_Rows{ rows },
	m_Columns{ cols }
{
}

void SpriteRenderer::SetLayer(const int& layer)
{
	IDrawable::SetLayer(layer);
}

int SpriteRenderer::GetLayer() const
{
	return IDrawable::GetLayer();
}

void SpriteRenderer::AssignSprite(Texture* sprite)
{
	m_SpritePtr = sprite;

	Rectf sliceRect{};
	sliceRect.width = m_SpritePtr->GetWidth() / float(m_Rows);
	sliceRect.height = m_SpritePtr->GetHeight() / float(m_Columns);
	sliceRect.left = 0;
	sliceRect.bottom = sliceRect.height;
	Slice(sliceRect);
}

void SpriteRenderer::Draw() const
{
	if (m_SpritePtr == nullptr) return;
	if (!m_GameObject->IsActive()) return;

	glPushMatrix();

	// Move according to position
	glTranslatef(m_Transform->position.x, m_Transform->position.y, 0);

	// Handle flipping
	glScalef(m_FlipX ? -1 : 1, 1, 1);
	glScalef(1, m_FlipY ? -1 : 1, 1);

	// Draw centred on position
	m_SpritePtr->Draw(Rectf(-m_Slice.width * m_Transform->scale.x / 2, 
								-m_Slice.height * m_Transform->scale.y / 2, 
								m_Slice.width * m_Transform->scale.x, 
							m_Slice.height * m_Transform->scale.y), 
						m_Slice);

	glPopMatrix();
}

Rectf SpriteRenderer::GetBounds() const
{
	if (m_SpritePtr != nullptr)
	{
		return Rectf(m_Transform->position.x - m_SpritePtr->GetWidth()/2, 
					m_Transform->position.y - m_SpritePtr->GetHeight()/2,
						(m_SpritePtr->GetWidth() / float(m_Columns)) * m_Transform->scale.x,
						(m_SpritePtr->GetHeight() / float(m_Rows)) * m_Transform->scale.y);
	}
	Print(">>Warning<< No sprite has been loaded.\n", TextColor::Red);
	return Rectf{};
}

void SpriteRenderer::Slice(const Rectf& slice)
{
	m_Slice = slice;
}

void SpriteRenderer::DebugDraw() const
{
	const Rectf sprite{  m_Transform->position.x - GetBounds().width / 2,
						m_Transform->position.y - GetBounds().height / 2,
						GetBounds().width, GetBounds().height };

	DrawRectColored(sprite);
}