#pragma once

class SpriteRenderer;

class Animator final: public Component
{
public:
	Animator();
	void Draw() const;

private:
	SpriteRenderer* m_pSpriteRenderer;
	const Texture* m_Sprite;
};