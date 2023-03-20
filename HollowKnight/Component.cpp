#include "pch.h"
#include "Component.h"

#include "GameObject.h"

Component::Component(const std::string name) : Object(&name),
m_GameObject{nullptr},
m_Transform{nullptr}
{
}

void Component::Update(const float& deltaTime)
{
	// Virtual
}

Component::~Component()
{
	if (m_GameObject != nullptr)
		m_GameObject->RemoveComponent(this);
}