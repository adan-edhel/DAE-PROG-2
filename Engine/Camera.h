#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "Vector2.h"
#include "structs.h"

class Camera final : public Component, IDrawable
{
public:
	inline static Camera* m_MainPtr{nullptr};

	Camera(const Vector2& screen);
	~Camera() override = default;
	void SetTarget(Transform& target);
	void SetLevelBoundaries(const Rectf& levelBoundaries);

private:
	Transform* m_TargetPtr;
	Rectf m_Boundaries;
	float m_PixelWidth;
	float m_PixelHeight;

	Vector2 Track() const;
	void Clamp(Vector2& bottomLeftPos) const;
	void Draw() override;
};
