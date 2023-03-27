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
	virtual void Update(const float& deltaTime);

private:
	void Initialize(GameObject* gameObject);
};