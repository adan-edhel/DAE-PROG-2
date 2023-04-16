#pragma once
#include "Component.h"
#include <map>

enum class AnimType;
class SpriteRenderer;

class Animator final: public Component
{
public:
	float m_PlaySpeed{ 1 };

	Animator();
	void Start() override;
	void PlayAnimation(const std::string& name);
	void AssignAnimations(std::map<std::string, Animation*>* anims);

private:
	Animation* m_CurrentAnim{};
	SpriteRenderer* m_SpriteRend{};
	std::map<std::string, Animation*>* m_Clips{};

	~Animator() override = default;
	void Update(const float& deltaTime) override;
};