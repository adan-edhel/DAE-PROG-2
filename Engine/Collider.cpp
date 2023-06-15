#include "Collider.h"

#include "AmrothUtils.h"
#include "utils.h"

#include "Transform.h"
#include "GameObject.h"

void Collider::OnEnable()
{
	s_AllColliders.push_back(this);
}

void Collider::OnDisable()
{
	s_AllColliders.erase(std::remove(s_AllColliders.begin(), s_AllColliders.end(), this), s_AllColliders.end());
	m_OverlappingColliders.clear();
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
	for (int i = 0; i < s_AllColliders.size(); i++)
	{
		// Skip itself
		if (s_AllColliders[i] == this) continue;

		// Skip if already collided
		if (Contains(m_OverlappingColliders, s_AllColliders[i])) continue;

		// Skip inactive collider
		if (!s_AllColliders[i]->m_GameObject->IsActive() || !s_AllColliders[i]->m_IsEnabled) continue;

		// Enter collision
		if (utils::IsOverlapping(m_Collider, s_AllColliders[i]->m_Collider))
		{
			// Add to list already collided with
			m_OverlappingColliders.push_back(s_AllColliders[i]);

			// Send collision message to all components
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionEnter(*s_AllColliders[i]);
			}

			//if (CORE::s_DebugMode)
			//{
			//	Print(m_GameObject->m_Name, TextColor::Yellow);
			//	Print(" collided ", TextColor::Lightgreen);
			//	Print(otherCollider->m_GameObject->m_Name + "\n", TextColor::Yellow);
			//}
		}
	}

	for (Collider* otherCollider : m_OverlappingColliders)
	{
		// Remove if collider isn't valid
		if (!Contains(s_AllColliders, otherCollider))
		{
			m_OverlappingColliders.erase(std::remove(m_OverlappingColliders.begin(), m_OverlappingColliders.end(), otherCollider), m_OverlappingColliders.end());
			continue;
		}

		// Exit collision
		if (!utils::IsOverlapping(m_Collider, otherCollider->m_Collider))
		{
			// Send collision message to all components
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionExit(*otherCollider);
			}

			// Erase from list already collided with
			m_OverlappingColliders.erase(std::remove(m_OverlappingColliders.begin(), m_OverlappingColliders.end(), otherCollider), m_OverlappingColliders.end());

			//if (CORE::s_DebugMode)
			//{
			//	Print(m_GameObject->m_Name, TextColor::Yellow);
			//	Print(" exited ", TextColor::Red);
			//	Print(otherCollider->m_GameObject->m_Name + "\n", TextColor::Yellow);
			//}

			continue;
		}

		// Ongoing collision
		if (utils::IsOverlapping(m_Collider, otherCollider->m_Collider))
		{
			if (!otherCollider->m_GameObject->IsActive() || !otherCollider->m_IsEnabled)
			{
				m_OverlappingColliders.erase(std::remove(m_OverlappingColliders.begin(), m_OverlappingColliders.end(), otherCollider), m_OverlappingColliders.end());
				otherCollider = nullptr;

				//if (CORE::s_DebugMode)
				//{
				//	Print(m_GameObject->m_Name, TextColor::Yellow);
				//	Print(" exited ", TextColor::Red);
				//	Print(otherCollider->m_GameObject->m_Name + "\n", TextColor::Yellow);
				//}

				continue;
			}

			// Send collision message to all components
			for (auto* component : m_GameObject->GetComponents())
			{
				component->OnCollisionStay(*otherCollider);
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
	DrawRectColored(m_Collider, Vector3(0, 0, 1), 2);
}