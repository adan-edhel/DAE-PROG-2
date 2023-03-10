#pragma once
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	class Animator : public IComponent
	{
	private:
		SpriteRenderer* m_SpriteRenderer;
		const Texture* m_Sprite;

	public:
		Animator();

		void Draw(Animation& anim) const;
	};
}

