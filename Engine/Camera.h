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
	~Camera() override = default;

	void SetTarget(Transform& target);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Vector2 GetPosition(const float& offset) const;
	void SetShake(float magnitude = 10.0f, float duration = 0.66f);

private:
	Transform* m_TargetPtr{};
	Rectf m_Boundaries;
	float m_PixelWidth;
	float m_PixelHeight;

	bool m_ShakeActive;
	float m_ShakeMagnitude;
	float m_ShakeDuration;
	float m_ShakeTimer;
	Vector2 m_ShakeOffset;

	void Update(const float& deltaTime) override;
	Vector2 Track() const;
	void Clamp(Vector2& bottomLeftPos) const;
	void CameraDraw() const override;
};
