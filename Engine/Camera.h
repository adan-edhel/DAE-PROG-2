#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Vector2.h"
#include "structs.h"

class Camera final : public Component, IUpdatable, IDrawable
{
public:
	inline static Camera* m_MainPtr{};

	Camera(const Vector2& screen);
	~Camera() override							= default;
	Camera(const Camera& other)					= delete;
	Camera(Camera&& other) noexcept				= delete;
	Camera& operator=(const Camera& other)		= delete;
	Camera& operator=(Camera&& other) noexcept	= delete;

	// Sets camera target object.
	void SetTarget(Transform& target);
	// Sets boundaries of the level.
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	// Returns camera position (with offset) for parallax.
	Vector2 GetPosition(const float& offset) const;
	// Shakes camera.
	void SetShake(float magnitude = 10.0f, float duration = 0.66f);

private:
	Transform* m_TargetPtr{};
	Rectf m_Boundaries;
	float m_PixelWidth;
	float m_PixelHeight;

	float m_ShakeTimer;
	float m_ShakeMagnitude;
	Vector2 m_ShakeOffset;

	void Update(const float& deltaTime) override;
	Vector2 Track() const;
	void Clamp(Vector2& bottomLeftPos) const;
	void CameraDraw() const override;
	bool IsShaking() const { return m_ShakeTimer > 0; }
};
