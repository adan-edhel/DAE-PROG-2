#include "pch.h"
#include "Component.h"

#include "Transform.h"
#include "GameObject.h"

Component::Component(const std::string name) : Object(&name)
{
}

void Component::Update(const float& deltaTime)
{
	// Virtual
}

Component::~Component()
{
	//UNDONE: Causes issues with access violation

	//if (m_GameObject != nullptr)
	//	m_GameObject->RemoveComponent(this);
}