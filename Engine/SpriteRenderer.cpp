#include "SpriteRenderer.h"

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

void SpriteRenderer::AssignSprite(Texture* sprite)
{
	m_SpritePtr = sprite;
	m_Transform->scale = Vector2(sprite->GetWidth(), sprite->GetHeight());

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

	glPushMatrix();

	// Move according to position
	glTranslatef(m_Transform->position.x, m_Transform->position.y, 0);

	// Handle flipping
	glScalef(m_FlipX ? -1 : 1, 1, 1);
	glScalef(1, m_FlipY ? -1 : 1, 1);

	// Draw centred on position
	m_SpritePtr->Draw(Point2f(-m_Slice.width / 2, -m_Slice.height / 2), m_Slice);

	glPopMatrix();
}

Rectf SpriteRenderer::GetBounds() const
{
	if (m_SpritePtr != nullptr)
	{
		return Rectf(m_Transform->position.x - m_SpritePtr->GetWidth()/2, 
					m_Transform->position.y - m_SpritePtr->GetHeight()/2,
						m_SpritePtr->GetWidth() / float(m_Columns),
						m_SpritePtr->GetHeight() / float(m_Rows));
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

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(sprite.left, sprite.bottom);
	glVertex2f(sprite.left, sprite.bottom + sprite.height);
	glVertex2f(sprite.left + sprite.width, sprite.bottom + sprite.height);
	glVertex2f(sprite.left + sprite.width, sprite.bottom);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}