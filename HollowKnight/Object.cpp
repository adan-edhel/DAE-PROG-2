#include "pch.h"
#include "Global.h"
#include "Object.h"

namespace AmrothFramework
{
	Object::Object()
	{
		Global::UpdateObjects.Connect(this, &Object::Update);
	}

	bool Object::isActive() const
	{
		return m_Active;
	}

	void Object::SetActive(const bool& active)
	{
		m_Active = active;
	}

	void Object::Update(const float& deltaTime)
	{
		if (!m_Active) return;
		transform.Update(deltaTime);
	}

	void Object::Draw() const
	{
	}

	Object::~Object()
	{
		Global::UpdateObjects.Disconnect(this, &Object::Update);
	}
}
