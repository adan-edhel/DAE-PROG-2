#include "AudioSource.h"

#include "AudioListener.h"
#include "AmrothUtils.h"
#include "SoundEffect.h"
#include "Transform.h"

AudioSource::AudioSource(bool loop, bool spatialBlend, bool playOnWake) :
	m_Loop{loop},
	m_PlayOnAwake{playOnWake},
	m_SpatialBlend{spatialBlend},
	m_MinDistance{200},
	m_MaxDistance{1000}
{
}

void AudioSource::Update(const float& deltaTime)
{
	if (m_UpdateCountdown < m_UpdateInterval)
	{
		m_UpdateCountdown += deltaTime;
	}

	if (m_AudioPtr != nullptr && CanUpdateVolume())
	{
		m_AudioPtr->SetVolume(static_cast<int>(GetAttenuatedVolume() * m_Volume));
		m_UpdateCountdown = 0;
	}
}

void AudioSource::SetClip(SoundEffect* audio)
{
	m_AudioPtr = audio;

	if (m_PlayOnAwake)
	{
		Play();
	}
}

bool AudioSource::IsPlaying() const
{
	if (m_AudioPtr == nullptr) return false;

	return m_AudioPtr->IsPlaying();
}

void AudioSource::Play() const
{
	if (m_AudioPtr == nullptr) return;

	m_AudioPtr->Play(m_Loop ? -1 : 0);
}

void AudioSource::Stop() const
{
	if (m_AudioPtr == nullptr) return;

	m_AudioPtr->Stop();
}

void AudioSource::Pause() const
{
	if (m_AudioPtr == nullptr) return;

	m_AudioPtr->Pause();
}

void AudioSource::Resume() const
{
	if (m_AudioPtr == nullptr) return;

	m_AudioPtr->Resume();
}

void AudioSource::SetVolume(float volume)
{
	Clamp(volume, 0.0f, 1.0f);
	m_Volume = volume;
}

float AudioSource::GetVolume() const
{
	return m_Volume;
}

void AudioSource::SetMinDistance(const float& distance)
{
	m_MinDistance = distance;
}

void AudioSource::SetMaxDistance(const float& distance)
{
	m_MaxDistance = distance;
}

float AudioSource::GetMinDistance() const
{
	return m_MinDistance;
}

float AudioSource::GetMaxDistance() const
{
	return m_MaxDistance;
}

int AudioSource::GetAttenuatedVolume() const
{
	const int maxVolume{ 128 };

	if (m_SpatialBlend == false) return maxVolume;

	int volume{};
	const float distance{ GetDistanceBetween(m_Transform->position.ToPoint2f(), AudioListener::m_MainPtr->m_Transform->position.ToPoint2f()) };

	if (distance <= m_MinDistance)
	{
		volume = maxVolume;
	}
	else if (distance >= m_MaxDistance)
	{
		volume = 0;
	}
	else
	{
		const float attenuationFactor = 1.0f - (distance - m_MinDistance) / (m_MaxDistance - m_MinDistance + 1);
		volume = static_cast<int>(attenuationFactor * maxVolume);

		//Print("Factor: " + std::to_string(attenuationFactor) + " " + "Sound: " + std::to_string(volume) + "\n");
	}

	return volume;
}
