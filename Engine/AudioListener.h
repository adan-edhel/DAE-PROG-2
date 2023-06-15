#pragma once
#include "Component.h"

class AudioListener final : public Component
{
public:
	// Main Audio Listener
	inline static AudioListener* m_MainPtr{};

	AudioListener() = default;
	~AudioListener() override = default;								
	AudioListener(const AudioListener& other) = delete;				
	AudioListener(AudioListener&& other) noexcept = delete;			
	AudioListener& operator=(const AudioListener& other) = delete;	
	AudioListener& operator=(AudioListener&& other) noexcept = delete;

	void Awake() override;
	void OnDestroy() override;
};