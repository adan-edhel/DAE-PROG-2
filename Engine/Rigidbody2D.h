#pragma once
#include "Component.h"

#include <vector>

#include "IDrawable.h"
#include "Vector2.h"

class Rigidbody2D final : public Component, public IDrawable
{
public:
	Rectf Collider{};

	bool m_IsStatic{ false };
	Vector2 m_Velocity{};
	bool isGrounded{ false };

	Rigidbody2D();
	~Rigidbody2D() override = default;

	void SetVelocity(const Vector2& velocity);
	void AddForce(const Vector2& force);

private:
	std::vector<std::vector<Point2f>> m_Vertices;

	float m_GravityModifier{};
	float m_Bounciness{ -0.75f };
	float m_Friction{ .9f };

	Rectf m_LevelBoundaries{};
	bool isAgainstWall{false};

	void Awake() override;
	void Update(const float& deltaTime) override;
	void VelocityDecay(const float& deltaTime);
	void SimulateGravity(const float& deltaTime);

	void UpdateCollider();
	void HandleCollision();
	bool IntersectsLine(const Rectf& rect, const Vector2& start, const Vector2& end, float& intersectMin, float& intersectMax);
	bool IsOnGround(const Rectf& rect, const float floorPos, const float tolerance);
	bool IsAgainstWall(const Rectf& rect, const float wallHeight, const float tolerance);
	void HandleFloorCollision(Rectf& collider, Vector2& velocity, bool& grounded, const float floorPos);
	void HandleWallCollision(Rectf& collider, Vector2& velocity, bool& againstWall, const float wallPos, const float wallHeight);
	void HandleBoundaryCollision(Rectf& collider, Vector2& velocity, bool& againstWall) const;

	void DebugDraw() const override;
};