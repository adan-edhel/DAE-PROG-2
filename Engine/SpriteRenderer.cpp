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

	m_SpritePtr->Draw(Point2f(-sliceRect.width / 2, 0), sliceRect);

	if (s_Debug)
	{
		glColor3f(1, 0, 0);
		DrawCircle(0, 0, 3, 90);
	}

	glPopMatrix();
}

Vector2 SpriteRenderer::Bounds() const
{
	if (m_SpritePtr != nullptr)
	{
		return Vector2(m_SpritePtr->GetWidth() / m_Columns, m_SpritePtr->GetHeight() / m_Rows);
	}
	Print(">>Warning<< No sprite has been loaded.\n", TextColor::Red);
	return Vector2{};
}

const Texture* SpriteRenderer::GetSprite() const
{
	return m_SpritePtr;
}