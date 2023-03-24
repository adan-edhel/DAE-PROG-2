#pragma once
#include "Object.h"

class Component : public Object
{
public:
	GameObject* m_GameObject{nullptr};
	Transform* m_Transform{nullptr};

	virtual void Update(const float& deltaTime);
	virtual ~Component() override;

protected:
	Component(const std::string name);

private:
	friend GameObject;
};