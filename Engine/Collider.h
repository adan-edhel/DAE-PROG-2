#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Vector2.h"

class Collider final : public Component, IDrawable
{
	class Rigidbody2D;

	friend Collision;
	friend Rigidbody2D;

public:
	Collider();
	~Collider() override;
	Collider(const Collider& other)					= default;	// copy constructor
	Collider(Collider&& other) noexcept				= delete;	// move constructor
	Collider& operator=(const Collider& other)		= default;	// copy operator
	Collider& operator=(Collider&& other) noexcept	= delete;	// move operator

	void SetSize(const float& sizeX, const float& sizeY);
	void SetSize(const Vector2& size);

	Vector2 GetCenter() const;
	Vector2 GetSize() const;
	Rectf GetBounds() const;

private:
	// All colliders in scene
	inline static std::vector<Collider*> s_AllColliders{};
	// All colliders overlapping with object
	std::vector<Collider*> m_OverlappingColliders{};
	// Collider Rect
	Rectf m_Collider{};
	// Collider offset
	Vector2 m_Translate{};

	void Update(const float& deltaTime) override;
	void DebugDraw() const override;

	void OnCollision();

	template<typename T>
	bool Contains(const std::vector<T>& object, const T& element)
	{
		auto it = std::find(
			object.begin(),
			object.end(),
			element);
		return it != object.end();
	}
};

struct Collision
{
	Collider* m_Collider;
	GameObject* m_GameObject;
	Transform* m_Transform;

	Collision(Collider& collider) :
		m_Collider{ &collider },
		m_GameObject{ collider.m_GameObject },
		m_Transform{ collider.m_Transform }
	{
	}
};