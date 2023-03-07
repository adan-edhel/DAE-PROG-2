#include "pch.h"
#include "Rigidbody2D.h"
#include "AmrothUtils.h"

Rigidbody2D::Rigidbody2D()
{
}

void Rigidbody2D::Update(const float& deltaTime)
{
	SimulateGravity(deltaTime);
}

void Rigidbody2D::SimulateGravity(const float& deltaTime)
{
	if (m_IsStatic) return;

	float& PositionY = m_Transform->position.y;

	m_GravityModifier += GRAVITY * deltaTime;
	PositionY += m_GravityModifier * deltaTime;

	if (PositionY <= 0)
	{
		m_GravityModifier *= m_Bounciness;
		PositionY = 0;
	}
}

Rigidbody2D::~Rigidbody2D()
{
}