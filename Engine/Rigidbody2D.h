#pragma once
#include "IDrawable.h"
#include "Component.h"

#include "Vector2.h"
#include <vector>

class Collider;

class Rigidbody2D final : public Component, IDrawable
{
public:
	bool m_IsStatic{ false };
	bool m_GravityEnabled{ true };
	Collider* m_Collider{};

	Rigidbody2D();
	~Rigidbody2D() override = default;
	Rigidbody2D(const Rigidbody2D& other) = delete;
	Rigidbody2D(Rigidbody2D&& other) noexcept = delete;
	Rigidbody2D& operator=(const Rigidbody2D& other) = delete;
	Rigidbody2D& operator=(Rigidbody2D&& other) noexcept = delete;

	void SetVelocity(const float& xVelocity, const float& yVelocity);
	void SetVelocity(const Vector2& velocity);
	void AddForce(const float& xForce, const float& yForce);
	void AddForce(const Vector2& force);

	bool isGrounded() const { return m_Grounded; }
	Vector2 GetVelocity() const { return m_Velocity; }

private:
	std::vector<std::vector<Point2f>> m_LevelBoundaries;

	bool m_Grounded{};
	Vector2 m_Velocity{};

	const float HorizontalDrag{ .9f };
	const float m_Bounciness{ -0.75f };
	const float m_CollisionTolerance{ 10 };

	void Start() override;
	void Update(const float& deltaTime) override;
	// Decays velocity over time.
	void DecayVelocity(const float& deltaTime);
	// Simulates gravity on object
	void SimulateGravity(const float& deltaTime);

	// -- Collisions --
	// Handles collisions between entities
	void HandleEntityCollisions();
	// Handles collisions with the floor
	void HandleFloorCollision(const Rectf& collider, Vector2& velocity, const float& floorPos);
	// Handles collisions with the ceiling
	void HandleCeilingCollision(const Rectf& collider, Vector2& velocity, const float& ceilingPos);
	// Handles collisions with the walls
	void HandleWallCollision(const Rectf& collider, Vector2& velocity, const float& wallPos, const float& wallHeight);
	// Handles collisions with level boundaries
	//void HandleBoundaryCollision(const Rectf& collider, Vector2& velocity) const; //TODO: Needs rework

	// --Assist Functions--
	// Checks for line intersections
	bool IntersectsLine(const Rectf& rect, const Vector2& start, const Vector2& end, float& intersectMin, float& intersectMax);
	// Checks for collisions with ground
	bool GroundCollision(const Rectf& rect, const float& floorPos, const float& tolerance) const;
	// Checks for collisions with ceilings
	bool CeilingCollision(const Rectf& rect, const float& ceilingPos, const float& tolerance) const;
	// Checks for collisions with walls
	bool WallCollision(const Rectf& rect, const float& wallHeight, const float& tolerance) const;

	// Debug
	void DebugDraw() const override;
};
