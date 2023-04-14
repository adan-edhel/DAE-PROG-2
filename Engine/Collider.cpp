#include "Collider.h"

#include "CORE.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Collider::Collider()
{
	s_AllColliders.emplace_back(this);
}

Collider::~Collider()
{
	s_AllColliders.erase(std::remove(s_AllColliders.begin(), s_AllColliders.end(), this), s_AllColliders.end());
}

void Collider::Awake()
{
	const auto bounds = m_GameObject->GetComponent<SpriteRenderer>()->Bounds();
	SetSize(bounds.x, bounds.y);
}

void Collider::Update(const float& deltaTime)
{
	if (m_GameObject != nullptr)
	{
		m_Collider.left = m_Transform->position.x - m_Collider.width / 2;
		m_Collider.bottom = m_Transform->position.y - m_Collider.height / 2;
	}
}

void Collider::SetSize(const float& sizeX, const float& sizeY) { SetSize(Vector2(sizeX, sizeY)); }
void Collider::SetSize(const Vector2& size)
{
	m_Collider.width = size.x;
	m_Collider.height = size.y;
}

Vector2 Collider::GetCenter() const
{
	return Vector2(m_Collider.left + m_Collider.width / 2, 
				m_Collider.bottom + m_Collider.height / 2);
}

Vector2 Collider::GetSize() const
{
	return Vector2(m_Collider.width, m_Collider.height);
}

Rectf Collider::GetBounds() const
{
	return m_Collider;
}

void Collider::DebugDraw() const
{
	if (CORE::s_DebugMode)
	{
		// Draw Collider

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0, 0, 1);
		glLineWidth(2);
		glBegin(GL_POLYGON);
		glVertex2f(m_Collider.left, m_Collider.bottom);
		glVertex2f(m_Collider.left, m_Collider.bottom + m_Collider.height);
		glVertex2f(m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height);
		glVertex2f(m_Collider.left + m_Collider.width, m_Collider.bottom);
		glEnd();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}