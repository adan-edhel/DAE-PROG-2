#include "Rigidbody2D.h"

#include "AmrothUtils.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "SVGParser.h"
#include "Transform.h"
#include "utils.h"

Rigidbody2D::Rigidbody2D() : Component("Rigidbody2D")
{
}

void Rigidbody2D::Awake()
{
	m_LevelBoundaries = Rectf(0, 0, 10000, 7000);

	const auto bounds = m_GameObject->GetComponent<SpriteRenderer>()->Bounds();
	Collider = Rectf{0,0,bounds.x, bounds.y};

	SVGParser::GetVerticesFromSvgFile("HollowKnight/LevelCollision.svg", m_Vertices);
}

void Rigidbody2D::Update(const float& deltaTime)
{
	if (!m_IsStatic)
	{
		UpdateCollider();
		HandleCollision();

		VelocityDecay(deltaTime);

		if (!isGrounded)
		{
			SimulateGravity(deltaTime);
		}

		m_Transform->position += m_Velocity;
	}
}

void Rigidbody2D::VelocityDecay(const float& deltaTime)
{
	m_Velocity.x *= m_Friction;
}

void Rigidbody2D::SimulateGravity(const float& deltaTime)
{
	//m_GravityModifier += GRAVITY * deltaTime;
	//m_GravityModifier *= m_Bounciness;

	AddForce(Vector2(0, GRAVITY * deltaTime));
}

void Rigidbody2D::SetVelocity(const Vector2& velocity)
{
	m_Velocity = velocity;
}

void Rigidbody2D::AddForce(const Vector2& force)
{
	using std::abs;

	if (abs(force.x) > 0) m_Velocity.x += force.x;
	if (abs(force.y) > 0) m_Velocity.y += force.y;
}

#pragma region Collision
void Rigidbody2D::UpdateCollider()
{
	Collider.left = m_Transform->position.x - Collider.width / 2;
	Collider.bottom = m_Transform->position.y;
}

void Rigidbody2D::HandleCollision()
{
	// Initialize flags to false
	isGrounded = false;
	isAgainstWall = false;

	// Check for collision with the level boundaries
	HandleBoundaryCollision(Collider, m_Velocity, isAgainstWall);

	// Check for collision with each shape in the level
	for (const auto& shape : m_Vertices)
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
			if (IntersectsLine(Collider, start, end, intersectMin, intersectMax))
			{
				// Calculate the position of the floor at the intersection point
				const float groundMin = start.y + intersectMin * pointDifference.y;
				const float groundMax = start.y + intersectMax * pointDifference.y;
				const float floorPos = std::max(groundMin, groundMax);

				// Handle floor collision
				HandleFloorCollision(Collider, m_Velocity, isGrounded, floorPos);

				// Check if the line segment is nearly horizontal (to avoid corner collision detection)
				if (std::abs(pointDifference.y) < 2.f) continue;

				// Calculate the position of the wall at the intersection point
				const float wallMin = start.x + intersectMin * pointDifference.x;
				const float wallMax = start.x + intersectMax * pointDifference.x;

				// Calculate the height of the wall at the intersection point
				const float wallHeight = std::max(start.y, end.y);
				const float wallPos = std::max(wallMin, wallMax);

				// Handle wall collision
				HandleWallCollision(Collider, m_Velocity, isAgainstWall, wallPos, wallHeight);
			}
		}
	}
}

bool Rigidbody2D::IntersectsLine(const Rectf& rect, const Vector2& start, const Vector2& end, float& intersectMin, float& intersectMax)
{
	if (!utils::IntersectRectLine(rect, start.ToPoint2f(), end.ToPoint2f(), intersectMin, intersectMax)) return false;
	if (intersectMax < 0 || intersectMin > 1) return false;
	return true;
}

bool Rigidbody2D::IsOnGround(const Rectf& rect, const float floorPos, const float tolerance)
{
	return floorPos - rect.bottom < tolerance;
}

bool Rigidbody2D::IsAgainstWall(const Rectf& rect, const float wallHeight, const float tolerance)
{
	return wallHeight - rect.bottom >= tolerance;
}

void Rigidbody2D::HandleFloorCollision(Rectf& collider, Vector2& velocity, bool& grounded, const float floorPos)
{
	if (IsOnGround(collider, floorPos, 10))
	{
		Clamp(velocity.y, 0, std::numeric_limits<float>::max());
		m_Transform->position.y = floorPos;
		grounded = true;
	}
}

void Rigidbody2D::HandleWallCollision(Rectf& collider, Vector2& velocity, bool& againstWall, const float wallPos, const float wallHeight)
{
	if (std::abs(velocity.x) > 0 && IsAgainstWall(collider, wallHeight, 10))
	{
		Vector2 clampRange{};
		if (wallPos > collider.left + collider.width / 2)
		{
			clampRange = Vector2(-std::numeric_limits<float>::max(), 0);
;		}
		else if (wallPos < collider.left + collider.width / 2)
		{
			clampRange = Vector2(0, std::numeric_limits<float>::max());
		}

		Clamp(velocity.x, clampRange.x, clampRange.y);
		againstWall = true;
	}
}

void Rigidbody2D::HandleBoundaryCollision(Rectf& collider, Vector2& velocity, bool& againstWall) const
{
	const Point2f topLeft{ collider.left, collider.bottom + collider.height };
	const Point2f topRight{ collider.left + collider.width, collider.bottom + collider.height };

	if (!utils::IsPointInRect(topLeft, m_LevelBoundaries))
	{
		if (topLeft.y >= m_LevelBoundaries.height)
		{
			velocity.y = 0;
			collider.bottom = m_LevelBoundaries.height - collider.height;

			if (collider.left <= 0)
			{
				velocity.x = 0;
				collider.left = 0;
			}

			if (collider.left >= m_LevelBoundaries.width - collider.width)
			{
				velocity.x = 0;
				collider.left = m_LevelBoundaries.width - collider.width;
			}
		}
		else
		{
			velocity.x = 0;
			collider.left = 0;

			againstWall = true;
		}
	}
	else if (!utils::IsPointInRect(topRight, m_LevelBoundaries))
	{
		velocity.x = 0;
		collider.left = m_LevelBoundaries.width - collider.width;

		againstWall = true;
	}
}

#pragma endregion

void Rigidbody2D::DebugDraw() const
{
	if (s_Debug == false) return;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 1);
	glLineWidth(2);

	// Draw Collider
	glBegin(GL_POLYGON);
	glVertex2f(Collider.left, Collider.bottom);
	glVertex2f(Collider.left, Collider.bottom + Collider.height);
	glVertex2f(Collider.left + Collider.width, Collider.bottom + Collider.height);
	glVertex2f(Collider.left + Collider.width, Collider.bottom);
	glEnd();

	glColor3f(1, 0, 0);
	glLineWidth(10);

	// Draw Level Colliders
	for (const auto& collider : m_Vertices)
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