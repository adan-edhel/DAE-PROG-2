#include "pch.h"
#include "Component.h"

#include "GameObject.h"

Component::Component(const std::string name) : Object(&name)
{
}

void Component::Update(const float& deltaTime)
{
}

Component::~Component()
{
	//UNDONE: Causes issues with access violation

	//if (m_GameObject != nullptr)
	//	m_GameObject->RemoveComponent(this);
}