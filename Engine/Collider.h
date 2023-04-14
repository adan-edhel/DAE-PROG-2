#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Vector2.h"

class Rigidbody2D;

class Collider : public Component, public IUpdatable, public IDrawable
{
	friend Rigidbody2D;
public:
	Collider();
	void SetSize(const float& sizeX, const float& sizeY);
	void SetSize(const Vector2& size);

	Vector2 GetCenter() const;
	Vector2 GetSize() const;
	Rectf GetBounds() const;

private:
	inline static std::vector<Collider*> s_AllColliders{};
	Rectf m_Collider{};

	~Collider() override;
	void Awake() override;
	void Update(const float& deltaTime) override;
	void DebugDraw() const override;
};
