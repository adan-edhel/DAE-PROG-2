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
	Animator(const Animator& other)					= delete;	// copy constructor
	Animator(Animator&& other) noexcept				= delete;	// move constructor
	Animator& operator=(const Animator& other)		= delete;	// copy operator
	Animator& operator=(Animator&& other) noexcept	= delete;	// move operator

	void Start() override;
	Animation* Current() const;
	void Play(const std::string& name);
	void AssignClips(std::map<std::string, Animation*>* anims);
	bool IsLoaded() const;

private:
	Animation* m_CurrentAnim{};
	SpriteRenderer* m_SpriteRend{};
	std::map<std::string, Animation*>* m_Clips{};

	~Animator() override = default;


	void Update(const float& deltaTime) override;
};