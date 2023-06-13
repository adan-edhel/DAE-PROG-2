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

protected:
	Component(const std::string& name = "");
	virtual ~Component() override = default;

	virtual void Awake();
	virtual void Start();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();
	virtual void Update(const float& deltaTime);

	virtual void OnCollisionEnter(const Collision& collision);
	virtual void OnCollisionStay(const Collision& collision);
	virtual void OnCollisionExit(const Collision& collision);

private:
	void Initialize(GameObject* gameObject);
};
