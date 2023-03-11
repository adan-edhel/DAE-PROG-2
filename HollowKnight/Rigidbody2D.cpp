#include "pch.h"
#include "Transform.h"
#include "Rigidbody2D.h"
#include "AmrothUtils.h"
#include "DelegateRegistry.h"


namespace AmrothFramework
{
	Rigidbody2D::Rigidbody2D()
	{
		DelegateRegistry::regularUpdate.Connect(this, &Rigidbody2D::Update);
	}

	void Rigidbody2D::SetVelocity(const Vector2& velocity)	{ m_Velocity = velocity; }
	void Rigidbody2D::AddForce(const Vector2& force)		{ m_Velocity += force; }

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

		if (PositionY <= 0)
		{
			m_GravityModifier *= m_Bounciness;
			m_Velocity = Vector2(0, 0);
			PositionY = 0;
		}

		m_pTransform->position += m_Velocity;
	}

	Rigidbody2D::~Rigidbody2D()
	{
		DelegateRegistry::regularUpdate.Disconnect(this, &Rigidbody2D::Update);
	}
}
