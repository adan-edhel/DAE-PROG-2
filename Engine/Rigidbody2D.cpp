#include "Rigidbody2D.h"

#include "AmrothUtils.h"
#include "SVGParser.h"
#include "utils.h"

#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "CORE.h"

Rigidbody2D::Rigidbody2D() : Component("Rigidbody2D")
{
}

void Rigidbody2D::Awake()
{
	m_PlayArea = Rectf(0, 0, 10000, 7000);
	m_Collider = m_GameObject->GetComponent<Collider>();

	std::vector<std::vector<Point2f>> platforms;
	SVGParser::GetVerticesFromSvgFile("HollowKnight/Environment/LevelCollision.svg", m_LevelBoundaries);
	SVGParser::GetVerticesFromSvgFile("HollowKnight/Environment/PlatformCollision.svg", platforms);
	m_LevelBoundaries.insert(m_LevelBoundaries.end(), platforms.begin(), platforms.end());
}

void Rigidbody2D::Update(const float& deltaTime)
{
	if (!m_IsStatic)
	{
		OnCollisionEnter();

		DecayVelocity(deltaTime);

		if (!m_Grounded)
		{
			SimulateGravity(deltaTime);
		}

		m_Transform->position += m_Velocity;
	}
}

void Rigidbody2D::DecayVelocity(const float& deltaTime)
{
	m_Velocity.x *= HorizontalDrag;
}

void Rigidbody2D::SimulateGravity(const float& deltaTime)
{
	AddForce(Vector2(0, GRAVITY * deltaTime));
}

void Rigidbody2D::SetVelocity(const float& xVelocity, const float& yVelocity) { SetVelocity(Vector2(xVelocity, yVelocity)); }
void Rigidbody2D::SetVelocity(const Vector2& velocity)
{
	m_Velocity = velocity;
}

void Rigidbody2D::AddForce(const float& xForce, const float& yForce) { AddForce(Vector2(xForce, yForce)); }
void Rigidbody2D::AddForce(const Vector2& force)
{
	using std::abs;

	if (abs(force.x) > 0) m_Velocity.x += force.x;
	if (abs(force.y) > 0) m_Velocity.y += force.y;
}

#pragma region Collision
//----------------------------------------------------

#pragma region Handling
void Rigidbody2D::OnCollisionEnter()
{
	// Initialize flags to false
	m_Grounded = false;

	// Check for collision with each shape in the level
	for (const auto& shape : m_LevelBoundaries)
	{
		// Check each line segment of the shape
		for (size_t i = 0; i < shape.size(); i++)
		{
			// Get the start and end points of the line segment
			const Vector2 start{ shape[i] };
			const Vector2 end{ shape[(i + 1) % shape.size()] };

			// Calculate the difference vector between the start and end points
			const Vector2 pointDifference{ end - start };

			// Initialize variables to store the intersection points
			float intersectMin{};
			float intersectMax{};

			// Check if there is an intersection between the player shape and the line segment
			if (IntersectsLine(m_Collider->GetBounds(), start, end, intersectMin, intersectMax))
			{
				// Calculate the position of the line at the intersection point
				const float lineMin = start.y + intersectMin * pointDifference.y;
				const float lineMax = start.y + intersectMax * pointDifference.y;

				// Handle ceiling collision
				const float ceilingPos = std::min(lineMin, lineMax);
				HandleCeilingCollision(m_Collider->GetBounds(), m_Velocity, ceilingPos);

				// Handle floor collision
				const float floorPos = std::max(lineMin, lineMax);
				HandleFloorCollision(m_Collider->GetBounds(), m_Velocity, floorPos);

				// Check if the line segment is nearly horizontal (to avoid corner collision detection)
				if (std::abs(pointDifference.y) < 2.f) continue;

				// Calculate the position of the wall at the intersection point
				const float wallMin = start.x + intersectMin * pointDifference.x;
				const float wallMax = start.x + intersectMax * pointDifference.x;

				// Calculate the height of the wall at the intersection point
				const float wallHeight = std::max(start.y, end.y);
				const float wallPos = std::max(wallMin, wallMax);

				// Handle wall collision
				HandleWallCollision(m_Collider->GetBounds(), m_Velocity, wallPos, wallHeight);
			}
		}
	}
}

void Rigidbody2D::HandleFloorCollision(const Rectf& collider, Vector2& velocity, const float& floorPos)
{
	if (GroundCollision(collider, floorPos, m_CollisionTolerance))
	{
		Clamp(velocity.y, 0, std::numeric_limits<float>::max());
		m_Transform->position.y = floorPos + m_Collider->GetSize().y / 2;
		m_Grounded = true;
	}
}

void Rigidbody2D::HandleCeilingCollision(const Rectf& collider, Vector2& velocity, const float& ceilingPos)
{
	if (CeilingCollision(collider, ceilingPos, m_CollisionTolerance))
	{
		Clamp(velocity.y, std::numeric_limits<float>::min(), 0);
		m_Transform->position.y = ceilingPos - m_Collider->GetSize().y / 2;
	}
}

void Rigidbody2D::HandleWallCollision(const Rectf& collider, Vector2& velocity, const float& wallPos, const float& wallHeight)
{
	if (std::abs(velocity.x) > 0 && WallCollision(collider, wallHeight, m_CollisionTolerance))
	{
		Vector2 clampRange{};
		if (wallPos > collider.left + collider.width / 2)
		{
			clampRange = Vector2(-std::numeric_limits<float>::max(), 0);
		}
		else if (wallPos < collider.left + collider.width / 2)
		{
			clampRange = Vector2(0, std::numeric_limits<float>::max());
		}
		Clamp(velocity.x, clampRange.x, clampRange.y);
	}
}
//void Rigidbody2D::HandleBoundaryCollision(const Rectf& collider, Vector2& velocity) const
//{
//
//	const Point2f topLeft{ collider.left, collider.bottom + collider.height };
//	const Point2f topRight{ collider.left + collider.width, collider.bottom + collider.height };
//
//	if (!utils::IsPointInRect(topLeft, m_PlayArea))
//	{
//		if (topLeft.y >= m_PlayArea.height)
//		{
//			velocity.y = 0;
//			m_Transform->position.y = m_PlayArea.height - collider.height;
//
//			if (collider.left <= 0)
//			{
//				velocity.x = 0;
//				m_Transform->position.x = 0;
//			}
//
//			if (m_Transform->position.x >= m_PlayArea.width - collider.width)
//			{
//				velocity.x = 0;
//				m_Transform->position.y = m_PlayArea.width - collider.width;
//			}
//		}
//		else
//		{
//			velocity.x = 0;
//			m_Transform->position.x = 0;
//		}
//	}
//	else if (!utils::IsPointInRect(topRight, m_PlayArea))
//	{
//		velocity.x = 0;
//		m_Transform->position.x = m_PlayArea.width - collider.width;
//	}
//}
#pragma endregion

//---------------- Assisting Functions----------------

bool Rigidbody2D::IntersectsLine(const Rectf& rect, const Vector2& start, const Vector2& end, float& intersectMin, float& intersectMax)
{
	if (!utils::IntersectRectLine(rect, start.ToPoint2f(), end.ToPoint2f(), intersectMin, intersectMax)) return false;
	if (intersectMax < 0 || intersectMin > 1) return false;
	return true;
}

bool Rigidbody2D::CeilingCollision(const Rectf& rect, const float& ceilingPos, const float& tolerance) const
{
	const float colliderTop = rect.bottom + rect.height;

	const bool isBelowCeiling = colliderTop <= ceilingPos + tolerance;
	const bool isAboveCeiling = rect.bottom <= ceilingPos;

	return isBelowCeiling && isAboveCeiling;
}

bool Rigidbody2D::GroundCollision(const Rectf& rect, const float& floorPos, const float& tolerance) const
{
	return floorPos - rect.bottom < tolerance;
}

bool Rigidbody2D::WallCollision(const Rectf& rect, const float& wallHeight, const float& tolerance) const
{
	return wallHeight - rect.bottom >= tolerance;
}
//----------------------------------------------------
#pragma endregion

void Rigidbody2D::DebugDraw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 0, 0);
	glLineWidth(10);

	// Draw Level Colliders
	for (const auto& collider : m_LevelBoundaries)
	{
		glBegin(GL_POLYGON);
		for (auto& point : collider)
		{
			glVertex2f(point.x, point.y);

		}
		glEnd();
	}

	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}