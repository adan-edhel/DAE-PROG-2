#pragma once
#include <map>

class SpriteRenderer;

class Animator final: public Component
{
public:
	float m_AnimationSpeed{ 1 };

	Animator();
	void Play(Animation*) const;

private:
	std::map<Animation, std::string> animations;

	SpriteRenderer* m_pSpriteRenderer;

	void Update(const float& deltaTime) override;
};