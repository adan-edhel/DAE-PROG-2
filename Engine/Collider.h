#pragma once
#include "Component.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Vector2.h"

class Collider final : public Component, public IUpdatable, public IDrawable
{
	class Rigidbody2D;
	friend Rigidbody2D;

public:
	Collider();
	~Collider() override;

	void SetSize(const float& sizeX, const float& sizeY);
	void SetSize(const Vector2& size);

	Vector2 GetCenter() const;
	Vector2 GetSize() const;
	Rectf GetBounds() const;

private:
	inline static std::vector<Collider*> s_AllColliders{};
	std::vector<Collider*> m_OverlappingColliders{};
	Rectf m_Collider{};
	Vector2 m_Translate{};

	void Awake() override;
	void OnCollision();
	void Update(const float& deltaTime) override;
	void DebugDraw() const override;

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