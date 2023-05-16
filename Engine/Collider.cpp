#include "Collider.h"

#include "AmrothUtils.h"
#include "utils.h"

#include "CORE.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Collider::Collider() : Component("Collider")
{
	s_AllColliders.emplace_back(this);
}

Collider::~Collider()
{
	s_AllColliders.erase(std::remove(s_AllColliders.begin(), s_AllColliders.end(), this), s_AllColliders.end());
}

void Collider::Awake()
{
	SetSize(m_Transform->scale);
}

void Collider::Update(const float& deltaTime)
{
	m_Collider.left = m_Transform->position.x + m_Translate.x;
	m_Collider.bottom = m_Transform->position.y + m_Translate.y;

	OnCollision();
}

void Collider::OnCollision()
{
	// Loop through all colliders
	for (const auto& otherCollider : s_AllColliders)
	{
		// Skip itself
		if (otherCollider == this) continue;

		// Skip already collided
		if (Contains(m_OverlappingColliders, otherCollider)) continue;

		// Enter collision
		if (utils::IsOverlapping(m_Collider, otherCollider->m_Collider))
		{
			// Add to list already collided with
			m_OverlappingColliders.emplace_back(otherCollider);

			// Send collision message to all components
			Collider collision{ *otherCollider };
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionEnter(collision);
			}

			if (CORE::s_DebugMode)
			{
				Print(m_GameObject->m_Name, TextColor::Yellow);
				Print(" collided ", TextColor::Lightgreen);
				Print(otherCollider->m_GameObject->m_Name + "\n", TextColor::Yellow);
			}
		}
	}

	for (const auto& otherCollider : m_OverlappingColliders)
	{
		// Exit collision
		if (!utils::IsOverlapping(m_Collider, otherCollider->m_Collider))
		{
			// Send collision message to all components
			Collider collision{ *otherCollider };
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionExit(collision);
			}

			// Add to list already collided with
			m_OverlappingColliders.erase(std::remove(m_OverlappingColliders.begin(), m_OverlappingColliders.end(), otherCollider), m_OverlappingColliders.end());

			if (CORE::s_DebugMode)
			{
				Print(m_GameObject->m_Name, TextColor::Yellow);
				Print(" exited ", TextColor::Red);
				Print(otherCollider->m_GameObject->m_Name + "\n", TextColor::Yellow);
			}

			continue;
		}

		// Ongoing collision
		if (utils::IsOverlapping(m_Collider, otherCollider->m_Collider))
		{
			// Send collision message to all components
			Collider collision{ *otherCollider };
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionStay(collision);
			}
		}
	}
}

void Collider::SetSize(const float& sizeX, const float& sizeY) { SetSize(Vector2(sizeX, sizeY)); }
void Collider::SetSize(const Vector2& size)
{
	m_Collider.width = size.x;
	m_Collider.height = size.y;

	m_Translate = Vector2{-m_Collider.width/2, -m_Collider.height/2};
}

Vector2 Collider::GetCenter() const
{
	return m_Transform->position + m_Translate;
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
	if (!m_GameObject->IsActive()) return;

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