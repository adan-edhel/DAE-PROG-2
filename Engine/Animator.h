#pragma once
#include "Component.h"
#include <map>

class SpriteRenderer;

enum class AnimType;
struct Animation;

class Animator final: public Component
{
public:
	float m_PlaybackSpeed{ 1 };

	Animator();
	void Start() override;
	void Play(const std::string& name);
	void AssignClips(std::map<std::string, Animation*>* anims);

private:
	Animation* m_CurrentAnim{};
	SpriteRenderer* m_SpriteRend{};
	std::map<std::string, Animation*>* m_Clips{};

	~Animator() override = default;
	void Update(const float& deltaTime) override;
};