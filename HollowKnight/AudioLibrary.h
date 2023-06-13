#pragma once
#include <map>
#include "AudioSource.h"

class SoundEffect;

enum class Music
{
	Title
};

enum class Audio
{
	ButtonHighlight,
	ButtonConfirm,
	HeroFootstep,
	HeroJump,
	HeroDash,
	HeroSword,
	SoulPickup,
	EnemyDamage,
	HeroLandHard,
	HeroLandSoft,
	BuzzerStartle,
	BuzzerFly,
	Crawler,
	Blizzard,
};

class AudioLibrary final
{
public:
	AudioLibrary();
	~AudioLibrary();
	AudioLibrary(const AudioLibrary& other) = delete;					// copy constructor
	AudioLibrary(AudioLibrary&& other) noexcept = delete;				// move constructor
	AudioLibrary& operator=(const AudioLibrary& other) = delete;		// copy operator
	AudioLibrary& operator=(AudioLibrary&& other) noexcept = delete;	// move operator

	static void PlayClip(const Audio& clip, bool loop = false);
	static SoundEffect* GetClip(const Audio& clip);
	static SoundEffect* GetClip(const Music& clip);

private:
	inline static AudioSource m_UISource{};

	inline static std::map<Music, SoundEffect*> s_MusicClips;
	void LoadClip(const Music& clip, const std::string& path);

	inline static std::multimap<Audio, SoundEffect*> s_AudioClips;
	void LoadClip(const Audio& clip, const std::string& path);
};