#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component(const std::string& name) : Object(name)
{
}

void Component::Awake()
{
}

void Component::Start()
{
}

void Component::Update(const float& deltaTime)
{
}

void Component::Initialize(GameObject* gameObject)
{
	m_GameObject = gameObject;
	m_Transform = gameObject->GetComponent<Transform>();
}