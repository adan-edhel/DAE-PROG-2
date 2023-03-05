#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class Object : public Transform
	{
	public:
		Transform* transform{ this };

		Object();
		~Object();

		void Update(const float& deltaTime) override;
		void SetActive(const bool& active);
	private:
		// Properties
		bool m_Active{ true };
	};
}
