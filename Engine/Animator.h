#pragma once
#include "Component.h"
#include <map>

class SpriteRenderer;

class Animator final: public Component
{
public:
	float m_AnimationSpeed{ 1 };

	Animator();
	~Animator() override = default;

	void Awake() override;
	void Play(Animation*) const;

private:
	SpriteRenderer* m_pSpriteRenderer{nullptr};

	std::map<Animation, std::string> animations;

	void Update(const float& deltaTime) override;
};