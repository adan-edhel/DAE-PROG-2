#pragma once
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	class Animator : public IComponent
	{
	private:
		SpriteRenderer* m_SpriteRenderer;

	public:
		Animator();
	};
}

