#include "pch.h"
#include "Object.h"

namespace AmrothFramework
{
	Object::Object()
	{

	}

	void Object::SetActive(const bool& active)
	{
		m_Active = active;
	}

	void Object::Update(const float& deltaTime)
	{
		if (!m_Active) return;

		Transform::Update(deltaTime);
		std::cout << "Object Updates \n";
	}

	Object::~Object()
	{
	}
}
