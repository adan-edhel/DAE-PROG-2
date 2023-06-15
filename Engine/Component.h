#pragma once
#include "Object.h"

class Collider;
struct Collision;

class Component : public Object
{
	friend GameObject;
	friend Collider;

public:
	GameObject* m_GameObject{};
	Transform* m_Transform{};

	bool m_IsEnabled{ true };

	Component(const Component& other) = delete;					// copy constructor
	Component(Component&& other) noexcept = delete;				// move constructor
	Component& operator=(const Component& other) = delete;		// copy operator
	Component& operator=(Component&& other) noexcept = delete;	// move operator

protected:
	Component(const std::string& name = "");
	~Component() override = default;

	// Fires after object creation for initialization.
	virtual void Awake();
	// Fires after the Awake function, and each time object is set to active.
	virtual void OnEnable();
	// Fires after OnEnable.
	virtual void Start();

	// Updates each frame.
	virtual void Update(const float& deltaTime);

	// Fires when collision occurs with other objects.
	virtual void OnCollisionEnter(const Collision& collision);
	// Fires while collision with other objects continue.
	virtual void OnCollisionStay(const Collision& collision);
	// Fires when collision ends with objects.
	virtual void OnCollisionExit(const Collision& collision);

	// Fires when object is set to inactive, and before destruction.
	virtual void OnDisable();
	// Fires when object is destroyed.
	virtual void OnDestroy();

private:
	// Initialize component references for GameObject & object Transform.
	void Initialize(GameObject* gameObject);
};
