#include "Rigidbody2D.h"

#include "AmrothUtils.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "utils.h"

Rigidbody2D::Rigidbody2D() : Component("Rigidbody2D")
{
}

void Rigidbody2D::Awake()
{
	const auto sprite = m_GameObject->GetComponent<SpriteRenderer>()->GetSprite();
	Collider = Rectf{ m_Transform->position.x - sprite->GetWidth()/2,
					m_Transform->position.y,
					sprite->GetWidth(),
					sprite->GetHeight() };
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
	if (utils::Raycast(m_Vertices[0], ray1, ray2, hitInfo))
	{
		m_Transform->position.y = hitInfo.intersectPoint.y;
		m_Velocity.y = 0;
		Print("GROUNDED!\n");
	}
}

bool Rigidbody2D::isGrounded()
{
	Point2f ray1(m_Transform->position.x, m_Transform->position.y - 10.0f);
	Point2f ray2(m_Transform->position.x, m_Transform->position.y);

	utils::HitInfo hitInfo{};
	return utils::Raycast(m_Vertices[0], ray1, ray2, hitInfo);
}