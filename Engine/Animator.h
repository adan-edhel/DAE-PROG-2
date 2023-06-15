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
	~Animator() override = default;
	Animator(const Animator& other) = delete;				
	Animator(Animator&& other) noexcept = delete;			
	Animator& operator=(const Animator& other) = delete;	
	Animator& operator=(Animator&& other) noexcept = delete;

	void Start() override;

	// Returns currently playing animation
	Animation* Current() const;
	// Plays given animation, if available
	void Play(const std::string& name);
	// Assigns clips to the animator
	void AssignClips(std::map<std::string, Animation*>* anims);
	// Returns whether the animator has clips loaded
	bool IsLoaded() const;

private:
	Animation* m_CurrentAnimPtr{};
	SpriteRenderer* m_SpriteRendererPtr{};
	std::map<std::string, Animation*>* m_Clips{};

	void Update(const float& deltaTime) override;
};