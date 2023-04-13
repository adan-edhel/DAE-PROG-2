#pragma once
#include "Component.h"

#include <vector>
#include "Vector2.h"

class Rigidbody2D final : public Component
{
public:

	Rectf Collider{};
	std::vector<std::vector<Point2f>> m_Vertices;

	bool m_IsStatic{ false };
	Vector2 m_Velocity{};

	bool isGrounded();

	Rigidbody2D();
	void SetVelocity(const Vector2& velocity);
	void AddForce(const Vector2& force);
	~Rigidbody2D() override = default;

private:
	float m_GravityModifier{};
	float m_Bounciness{ -0.75f };
	float m_Friction{ 99 };

	void Awake() override;
	void Update(const float& deltaTime) override;
	void VelocityDecay(const float& deltaTime);
	void SimulateGravity(const float& deltaTime);
	void HandleCollision();
};
