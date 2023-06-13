#pragma once
#include "Component.h"

class AudioListener : public Component
{
public:
	inline static AudioListener* m_MainPtr{};

	AudioListener();
	void Awake() override;
	void OnDisable() override;
};