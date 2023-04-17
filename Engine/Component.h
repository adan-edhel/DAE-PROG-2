#pragma once
#include "Object.h"

class Component : public Object
{
	friend GameObject;

public:
	GameObject* m_GameObject{};
	Transform* m_Transform{};

protected:
	Component(const std::string& name = "");
	virtual ~Component() override = default;

	virtual void Awake();
	virtual void Start();
	virtual void Update(const float& deltaTime);
	virtual void OnCollisionEnter(const GameObject* collision);

private:
	void Initialize(GameObject* gameObject);
};