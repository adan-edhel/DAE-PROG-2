#pragma once
#include <iostream>
#include <map>

class SpriteRenderer;

class Animator final: public Component
{
public:
	Animator();
	void Draw() const;

private:
	std::map<Animation, std::string> animations;

	const Texture* m_Sprite;
	SpriteRenderer* m_pSpriteRenderer;

	float m_AccumulatedTime{};

	void Update(const float& deltaTime) override;
};