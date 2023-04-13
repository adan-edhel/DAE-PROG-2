#include "Camera.h"

#include "AmrothUtils.h"
#include "Transform.h"

Camera::Camera(const Vector2& screen) :
	m_TargetPtr{nullptr},
	m_PixelWidth{ screen.x },
	m_PixelHeight{ screen.y }
{
	if (m_MainPtr == nullptr) m_MainPtr = this;

	if (m_MainPtr == nullptr) Print("Main camera not assigned.", TextColor::Red);
}

void Camera::SetTarget(Transform& target)
{
	m_TargetPtr = &target;
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_Boundaries = levelBoundaries;
}

Vector2 Camera::Track() const
{
	return Vector2(m_TargetPtr->position.x - m_PixelWidth/2, m_TargetPtr->position.y - m_PixelHeight/2);
}

void Camera::Draw()
{
	if (m_TargetPtr != nullptr)
	{
		Vector2 centerPos{ Track() };
		Clamp(centerPos);
		glTranslatef(centerPos.x, centerPos.y, 0);
	}
}

void Camera::Clamp(Vector2& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_Boundaries.left)
	{
		bottomLeftPos.x = m_Boundaries.left + 1.0f;

	}
	if (bottomLeftPos.x + m_PixelWidth > m_Boundaries.left + m_Boundaries.width)
	{
		bottomLeftPos.x = m_Boundaries.left + m_Boundaries.width - m_PixelWidth;
	}
	if (bottomLeftPos.y < m_Boundaries.bottom)
	{
		bottomLeftPos.y = m_Boundaries.bottom;
	}
	if (bottomLeftPos.y + m_PixelHeight > m_Boundaries.bottom + m_Boundaries.height)
	{
		bottomLeftPos.y = m_Boundaries.bottom + m_Boundaries.height - m_PixelHeight;
	}
}