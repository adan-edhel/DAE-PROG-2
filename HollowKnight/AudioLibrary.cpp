#include "pch.h"
#include "AudioLibrary.h"
#include <SoundEffect.h>
#include <vector>

#include "CORE.h"

AudioLibrary::AudioLibrary()
{
	// Music
	LoadClip(Music::Title, "Audio/Music/TitleTheme.wav");
;
	// UI
	LoadClip(Audio::ButtonHighlight, "Audio/UI/ui_change_selection.wav");
	LoadClip(Audio::ButtonConfirm, "Audio/UI/ui_button_confirm.wav");

	// Hero
	LoadClip(Audio::HeroFootstep, "Audio/Game/Hero/hero_run_footsteps_stone.wav");
	LoadClip(Audio::HeroJump, "Audio/Game/Hero/hero_jump.wav");
	LoadClip(Audio::HeroDash, "Audio/Game/Hero/hero_dash.wav");
	LoadClip(Audio::HeroSword, "Audio/Game/Hero/sword_1.wav");
	LoadClip(Audio::HeroSword, "Audio/Game/Hero/sword_2.wav");
	LoadClip(Audio::HeroSword, "Audio/Game/Hero/sword_3.wav");
	LoadClip(Audio::HeroSword, "Audio/Game/Hero/sword_4.wav");
	LoadClip(Audio::HeroSword, "Audio/Game/Hero/sword_5.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_1.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_2.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_3.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_4.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_5.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_6.wav");
	LoadClip(Audio::SoulPickup, "Audio/Game/Hero/soul_pickup_7.wav");
	LoadClip(Audio::EnemyDamage, "Audio/Game/Enemies/enemy_damage.wav");
	LoadClip(Audio::HeroLandHard, "Audio/Game/Hero/hero_land_hard.wav");
	LoadClip(Audio::HeroLandSoft, "Audio/Game/Hero/hero_land_soft.wav");

	// Enemies
	LoadClip(Audio::BuzzerStartle, "Audio/Game/Enemies/buzzer_startle_01.wav");
	LoadClip(Audio::BuzzerStartle, "Audio/Game/Enemies/buzzer_startle_02.wav");
	LoadClip(Audio::BuzzerStartle, "Audio/Game/Enemies/buzzer_startle_03.wav");
	LoadClip(Audio::BuzzerFly, "Audio/Game/Enemies/buzzer_fly.wav");
	LoadClip(Audio::Crawler, "Audio/Game/Enemies/crawler.wav");

	// Ambience
	LoadClip(Audio::Blizzard, "Audio/Game/Ambience/blizzard_loop.wav");
}

AudioLibrary::~AudioLibrary()
{
	SoundEffect::StopAll();

	// Clear Songs
	for (const auto& entry : s_MusicClips)
	{
		delete entry.second;
	}
	s_MusicClips.clear();

	// Clear Audio Clips
	for (const auto& entry : s_AudioClips)
	{
		delete entry.second;
	}
	s_AudioClips.clear();
}

SoundEffect* AudioLibrary::GetClip(const Audio& clip)
{
	// Vector for matching audio clips
	std::vector<SoundEffect*> matchingClips{};

	// Find all matching clips in the multimap
	const auto range = s_AudioClips.equal_range(clip);
	for (auto it = range.first; it != range.second; ++it)
	{
		matchingClips.push_back(it->second);
	}

	// If there are more than a single clip, return a random one.
	if (matchingClips.size() > 1)
	{
		const int index = RandomRange(0, int(matchingClips.size()) - 1);
		if (CORE::s_DebugMode)
		{
			Print("Audioclip index: " + std::to_string(index) + "\n");
		}
		return matchingClips[index];
	}

	// If there's only a single clip, return it
	return matchingClips[0];
}

SoundEffect* AudioLibrary::GetClip(const Music& clip)
{
	return s_MusicClips.find(clip)->second;
}

void AudioLibrary::LoadClip(const Music& clip, const std::string& path)
{
	s_MusicClips.emplace(clip, new SoundEffect(path));
}

void AudioLibrary::LoadClip(const Audio& clip, const std::string& path)
{
	s_AudioClips.emplace(clip, new SoundEffect(path));
}
