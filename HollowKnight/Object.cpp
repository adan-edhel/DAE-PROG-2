#include "pch.h"
#include "Object.h"
#include "Delegates.h"

namespace AmrothFramework
{
	Object::Object() :
	transform{new Transform()}
	{
		Delegates::UpdateObjects.Connect(this, &Object::Update);
	}

	void Object::SetActive(const bool& active)
	{
		m_Active = active;
	}

	void Object::Update(const float& deltaTime)
	{
		if (!m_Active) return;

		transform->Update(deltaTime);
	}

	Object::~Object()
	{
		Delegates::UpdateObjects.Disconnect(this, &Object::Update);
		delete transform;
	}
}
