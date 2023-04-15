#pragma once
#include "Component.h"
#include <map>

class Animator final: public Component
{
	class SpriteRenderer;

public:
	float m_AnimationSpeed{ 1 };

	Animator();
	~Animator() override = default;

	void Awake() override;
	void Play(Animation*) const;

private:
	SpriteRenderer* m_pSpriteRenderer{};

	std::map<Animation, std::string> animations;

	void Update(const float& deltaTime) override;
};