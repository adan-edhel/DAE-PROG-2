#pragma once

namespace AmrothFramework
{
	class SpriteRenderer;

	class Animator : public IComponent
	{
	public:
		Animator();
		void Draw() const;

	private:
		SpriteRenderer* m_pSpriteRenderer;
		const Texture* m_Sprite;
	};
}

