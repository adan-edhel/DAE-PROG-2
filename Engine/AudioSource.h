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
	~AudioSource() override = default;
	AudioSource(const AudioSource& other) = delete;
	AudioSource(AudioSource&& other) noexcept = delete;
	AudioSource& operator=(const AudioSource& other) = delete;
	AudioSource& operator=(AudioSource&& other) noexcept = delete;

	// Assigns given clip to the audio source. Plays immediately if playOnWake is enabled.
	void AssignClip(SoundEffect* audio);
	// Returns if audio is currently playing. Paused audio still counts as playing.
	bool IsPlaying() const;
	// Plays assigned clip, if there is any.
	void Play() const;
	// Stops assigned clip.
	void Stop() const;
	// Pauses assigned clip, paused clips keep their channel occupied unless stopped.
	void Pause() const;
	// Resumes assigned clip.
	void Resume() const;

	// Sets volume for this audio source. Values clamped between 0.0f and 1.0f.
	void SetVolume(float volume);
	// Returns volume of this audio source.
	float GetVolume() const;

	// Sets minimum distance for audio attenuation.
	void SetMinDistance(const float& distance);
	// Gets minimum distance for audio attenuation.
	float GetMinDistance() const;
	// Sets maximum distance for audio attenuation.
	void SetMaxDistance(const float& distance);
	// Gets maximum distance for audio attenuation.
	float GetMaxDistance() const;

private:
	SoundEffect* m_AudioPtr{};
	float m_Volume{1};

	float m_MinDistance;
	float m_MaxDistance;

	float m_UpdateInterval{ 0.5f };
	float m_UpdateCountdown{m_UpdateInterval};

	void Update(const float& deltaTime) override;

	// Calculate volume depending on distance to the AudioListener.
	int AttenuateVolume() const;
	// Can update attenuated volume.
	bool CanUpdate() const { return m_UpdateCountdown >= m_UpdateInterval; }
};
