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
	Collider* m_Collider{};

	Rigidbody2D();
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

	~Rigidbody2D() override = default;
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void DecayVelocity(const float& deltaTime);
	void SimulateGravity(const float& deltaTime);

	// Collisions
	void CheckForCollision();
	void HandleFloorCollision(const Rectf& collider, Vector2& velocity, const float& floorPos);
	void HandleCeilingCollision(const Rectf& collider, Vector2& velocity, const float& ceilingPos);
	void HandleWallCollision(const Rectf& collider, Vector2& velocity, const float& wallPos, const float& wallHeight);
	//void HandleBoundaryCollision(const Rectf& collider, Vector2& velocity) const; //TODO: Needs rework

	// Assist Functions
	bool IntersectsLine(const Rectf& rect, const Vector2& start, const Vector2& end, float& intersectMin, float& intersectMax);
	bool GroundCollision(const Rectf& rect, const float& floorPos, const float& tolerance) const;
	bool CeilingCollision(const Rectf& rect, const float& ceilingPos, const float& tolerance) const;
	bool WallCollision(const Rectf& rect, const float& wallHeight, const float& tolerance) const;

	// Debug
	void DebugDraw() const override;
};
