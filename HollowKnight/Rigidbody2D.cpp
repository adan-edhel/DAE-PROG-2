#include "pch.h"
#include "Transform.h"
#include "Rigidbody2D.h"
#include "AmrothUtils.h"

Rigidbody2D::Rigidbody2D()
{
}

void Rigidbody2D::SetVelocity(const Vector2& velocity) { m_Velocity = velocity; }
void Rigidbody2D::AddForce(const Vector2& force)
{
	std::abs(force.x) > 0 ? m_Velocity.x += force.x : 0;
	std::abs(force.y) > 0 ? m_Velocity.y += force.y : 0;
}

void Rigidbody2D::Update(const float& deltaTime)
{
	if (!m_pIsActive) return;

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
	float& PositionY = m_pTransform->position.y;

	m_GravityModifier += GRAVITY * deltaTime;
	if (PositionY > 0)
	{
		AddForce(Vector2(0, GRAVITY * deltaTime));
	}

	// When on ground
	if (PositionY <= 0)
	{
		m_GravityModifier *= m_Bounciness;
		m_Velocity.y = 0;
		PositionY = 0;
	}

	m_pTransform->position += m_Velocity;
}