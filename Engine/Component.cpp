#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component(const std::string& name) : Object(name)
{
}

//UNDONE: Causes issues with access violation
//Component::~Component()
//{
//	if (m_GameObject != nullptr)
//		m_GameObject->RemoveComponent(this);
//}

void Component::Awake()
{
}

void Component::Update(const float& deltaTime)
{
}

void Component::Initialize(GameObject* gameObject)
{
	m_GameObject = gameObject;
	m_Transform = m_GameObject->GetComponent<Transform>();
}