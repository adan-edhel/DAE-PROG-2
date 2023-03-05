#pragma once
#include "Object.h"

namespace AmrothFramework
{
	class Behavior
	{
	public:
		Object* gameObject;

		Behavior();
		~Behavior();

		virtual void Update(const float& deltaTime);
	};
}