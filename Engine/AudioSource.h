#pragma once
#include "Component.h"

class SoundEffect;

class AudioSource final : public Component
{
public:
	bool m_Loop;
	bool m_PlayOnAwake;
	bool m_SpatialBlend;

	AudioSource(bool loop = false, bool spatialBlend = true, bool playOnWake = true);

	void SetClip(SoundEffect* audio);
	bool IsPlaying() const;
	void Play() const;
	void Stop() const;
	void Pause() const;
	void Resume() const;
	void SetVolume(float volume);
	float GetVolume() const;

	void SetMinDistance(const float& distance);
	void SetMaxDistance(const float& distance);
	float GetMinDistance() const;
	float GetMaxDistance() const;

private:
	SoundEffect* m_AudioPtr{};
	float m_Volume{1};

	float m_MinDistance;
	float m_MaxDistance;

	float m_UpdateInterval{ 0.5f };
	float m_UpdateCountdown{m_UpdateInterval};

	void Update(const float& deltaTime) override;

	int GetAttenuatedVolume() const;
	bool CanUpdateVolume() const { return m_UpdateCountdown >= m_UpdateInterval; }
};
