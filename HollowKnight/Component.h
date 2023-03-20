#pragma once
#include "Object.h"

#include "IUpdateEvent.h"

class Component : public Object, public IUpdateEvent
{
public:
	GameObject* m_GameObject;
	Transform* m_Transform;

	virtual void Update(const float& deltaTime) override;
	virtual ~Component() override;

protected:
	Component(const std::string name);

private:
	friend GameObject;
};