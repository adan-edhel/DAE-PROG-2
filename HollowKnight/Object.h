#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class Object
	{
	public:
		Transform* transform;

		Object();
		~Object();

		void Update(const float& deltaTime);
		void SetActive(const bool& active);

		bool isActive() const { return m_Active; }

	private:
		// Properties
		bool m_Active{ true };
	};
}
