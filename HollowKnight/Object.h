#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class Object
	{
	public:
		Transform transform{};

		Object();
		bool isActive() const;
		void SetActive(const bool& active);
		~Object();

	private:
		bool m_Active{ true };

		void Update(const float& deltaTime);
		void Draw() const;
	};
}
