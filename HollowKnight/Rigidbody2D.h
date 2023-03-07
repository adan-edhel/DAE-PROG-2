#pragma once
#include "Transform.h"

class Rigidbody2D : public IComponent
{
public:
	bool m_IsStatic{ false };

	Rigidbody2D();
	void Update(const float& deltaTime) override;
	~Rigidbody2D();

private:
	Vector2 m_Velocity{};

	float m_GravityModifier{};
	float m_Bounciness{-0.75f};

protected:
	void SimulateGravity(const float& deltaTime);
};

