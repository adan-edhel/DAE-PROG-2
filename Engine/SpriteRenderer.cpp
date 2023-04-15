#include "SpriteRenderer.h"

#include "AmrothUtils.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(const Texture* sprite, const int& rows, const int& cols) :
	Component("SpriteRenderer"),
	IDrawable(s_MidLayer),
	m_SpritePtr{ sprite },
	m_Rows{ rows },
	m_Columns{ cols }
{
}

void SpriteRenderer::AssignSprite(const Texture* sprite)
{
	m_SpritePtr = sprite;
	m_Transform->scale = Vector2(sprite->GetWidth(), sprite->GetHeight());
}

void SpriteRenderer::Draw() const
{
	if (m_SpritePtr == nullptr) return;

	Rectf sliceRect{};
	sliceRect.width		= m_SpritePtr->GetWidth()  / float(m_Rows);
	sliceRect.height	= m_SpritePtr->GetHeight() / float(m_Columns);
	sliceRect.left		= 0;
	sliceRect.bottom	= sliceRect.height;

	glPushMatrix();

	glTranslatef(m_Transform->position.x, m_Transform->position.y, 0);
	glScalef(m_FlipX ? -1 : 1, 1, 1);

	m_SpritePtr->Draw(Point2f(-sliceRect.width / 2, -sliceRect.height / 2), sliceRect);

	glPopMatrix();
}

Rectf SpriteRenderer::GetBounds() const
{
	if (m_SpritePtr != nullptr)
	{
		return Rectf(m_Transform->position.x - m_SpritePtr->GetWidth()/2, 
					m_Transform->position.y - m_SpritePtr->GetHeight()/2,
						m_SpritePtr->GetWidth() / m_Columns,
						m_SpritePtr->GetHeight() / m_Rows);
	}
	Print(">>Warning<< No sprite has been loaded.\n", TextColor::Red);
	return Rectf{};
}

const Texture* SpriteRenderer::GetSprite() const
{
	return m_SpritePtr;
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