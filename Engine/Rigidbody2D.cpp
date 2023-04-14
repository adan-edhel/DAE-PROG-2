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
	const auto bounds = m_GameObject->GetComponent<SpriteRenderer>()->Bounds();
	Collider = Rectf{0,0,bounds.x, bounds.y};

	SVGParser::GetVerticesFromSvgFile("HollowKnight/LevelCollision.svg", m_Vertices);
}

void Rigidbody2D::SetVelocity(const Vector2& velocity)
{
	m_Velocity = velocity;
}

void Rigidbody2D::AddForce(const Vector2& force)
{
	std::abs(force.x) > 0 ? m_Velocity.x += force.x : 0;
	std::abs(force.y) > 0 ? m_Velocity.y += force.y : 0;
}

void Rigidbody2D::Update(const float& deltaTime)
{
	Collider.left = m_Transform->position.x - Collider.width/2;
	Collider.bottom = m_Transform->position.y;

	if (!m_IsStatic)
	{
		VelocityDecay(deltaTime);
		SimulateGravity(deltaTime);

		m_Transform->position += m_Velocity;
	}
}

void Rigidbody2D::VelocityDecay(const float& deltaTime)
{
	m_Velocity.x *= m_Friction * deltaTime;
}

void Rigidbody2D::SimulateGravity(const float& deltaTime)
{
	//m_GravityModifier += GRAVITY * deltaTime;
	//m_GravityModifier *= m_Bounciness;

	if (isGrounded())
	{
		HandleCollision();
	}
	else
	{
		AddForce(Vector2(0, GRAVITY * deltaTime));
	}
}

void Rigidbody2D::HandleCollision()
{
	Point2f ray1(m_Transform->position.x, m_Transform->position.y);
	Point2f ray2(m_Transform->position.x, m_Transform->position.y - 10.0f);

	utils::HitInfo hitInfo{};

	for (const auto& collider : m_Vertices)
	{
		if (Raycast(collider, ray1, ray2, hitInfo))
		{
			m_Transform->position.y = hitInfo.intersectPoint.y;
			m_Velocity.y = 0;
			Print("GROUNDED!\n");
		}
	}
}

bool Rigidbody2D::isGrounded()
{
	Point2f ray1(m_Transform->position.x, m_Transform->position.y - 10.0f);
	Point2f ray2(m_Transform->position.x, m_Transform->position.y);

	utils::HitInfo hitInfo{};
	return utils::Raycast(m_Vertices[0], ray1, ray2, hitInfo);
}

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
	glBegin(GL_POLYGON);
	for (const auto& collider : m_Vertices)
	{
		for (auto& point : collider)
		{
			glVertex2f(point.x, point.y);
		}
	}
	glEnd();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}