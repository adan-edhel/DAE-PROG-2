#include "Rigidbody2D.h"

#include "AmrothUtils.h"
#include "Transform.h"

Rigidbody2D::Rigidbody2D() : Component("Rigidbody2D")
{
}

bool Rigidbody2D::isGrounded()
{
	return m_Transform->position.y < 0;
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

	if (!isGrounded())
	{
		AddForce(Vector2(0, GRAVITY * deltaTime));
		if (isGrounded())
		{
			m_Velocity.y = 0;
		}
	}
	else
	{
		m_Transform->position.y = 0;
	}

	m_Transform->position += m_Velocity;
}