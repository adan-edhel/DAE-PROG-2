#include "SpriteRenderer.h"

#include "AmrothUtils.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(const std::string& spritePath) :
	Component("SpriteRenderer"),
	IDrawable(s_MidLayer),
	m_DefaultSpritePtr{new Texture("default_circle.png")},
	m_SpritePtr{ m_DefaultSpritePtr },
	m_Rows{ 12 },
	m_Columns{ 12 }
{
}

SpriteRenderer::~SpriteRenderer()
{
	delete m_DefaultSpritePtr;
}

void SpriteRenderer::AssignSprite(const Texture* sprite)
{
	if (m_SpritePtr != nullptr)
	{
		m_SpritePtr = sprite;
	}
}

void SpriteRenderer::Draw() const
{
	Rectf sliceRect{};
	sliceRect.width		= m_SpritePtr->GetWidth()  / float(m_Rows);
	sliceRect.height	= m_SpritePtr->GetHeight() / float(m_Columns);
	sliceRect.left		= 0;
	sliceRect.bottom	= sliceRect.height;

	glPushMatrix();

	glTranslatef(m_Transform->position.x, m_Transform->position.y, 0);
	glScalef(m_FlipX ? -1 : 1, 1, 1);

	m_SpritePtr->Draw(Point2f(-sliceRect.width / 2, 0), sliceRect);

	glColor3f(1, 0, 0);
	DrawCircle(0, 0, 3, 90);

	glPopMatrix();
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