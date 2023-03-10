#include "pch.h"
#include "Rigidbody2D.h"
#include "AmrothUtils.h"

namespace AmrothFramework
{
	Rigidbody2D::Rigidbody2D()
	{

	}

	void Rigidbody2D::Update(const float& deltaTime)
	{
		if (!m_IsStatic)
		{
			VelocityDecay(deltaTime);
			SimulateGravity(deltaTime);
		}
	}

	void Rigidbody2D::SetVelocity(const Vector2& velocity)
	{
		m_Velocity = velocity;
	}

	void Rigidbody2D::AddForce(const Vector2& force)
	{
		m_Velocity += force;
	}

	void Rigidbody2D::SimulateGravity(const float& deltaTime)
	{
		float& PositionY = m_Transform->position.y;

		m_GravityModifier += GRAVITY * deltaTime;
		if (PositionY > 0)
		{
			AddForce(Vector2(0, GRAVITY * deltaTime));
		}

		if (PositionY <= 0)
		{
			m_GravityModifier *= m_Bounciness;
			m_Velocity = Vector2(0, 0);
			PositionY = 0;
		}

		m_Transform->position += m_Velocity;
	}

	void Rigidbody2D::VelocityDecay(const float& deltaTime)
	{
		m_Velocity.x *= m_Friction * deltaTime;
	}
}