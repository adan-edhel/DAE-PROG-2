#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class GameObject
	{
	public:
		Transform transform{};

		GameObject();
		bool isActive() const;
		void SetActive(const bool& active);
		~GameObject();

	private:
		bool m_Active{ true };

		void Update(const float& deltaTime);
		void Draw() const;
	};
}
