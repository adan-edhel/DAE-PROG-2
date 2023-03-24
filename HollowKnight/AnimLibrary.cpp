#include "pch.h"
#include "AnimLibrary.h"

#include "AmrothUtils.h"
#include "GameSettings.h"
#include "SpriteLibrary.h"

//TODO: Test animation clips

void AnimLibrary::Setup()
{
	if (GameSettings::s_DebugMode)
	{
		Print("Animation Library Being Setup...\n", TextColor::Lightgray);
	}

	KnightSetup();
	CrawlidSetup();
	VengeflySetup();

	m_HasBeenSetup = true;

	// Print information in the console
	if (GameSettings::s_DebugMode && m_DebugInfo)
	{
		Print("############## Animation Library ##############\n", TextColor::Darkgray);

		PrintInfo("Hollow Knight", m_KnightClips);
		PrintInfo("Crawlid", m_CrawlidClips);
		PrintInfo("Vengefly", m_VengeflyClips);

		Print("###############################################\n", TextColor::Darkgray);
	}
}

void AnimLibrary::Cleanup()
{
	DeleteClips(m_KnightClips);
	DeleteClips(m_CrawlidClips);
	DeleteClips(m_VengeflyClips);

	if (GameSettings::s_DebugMode)
	{
		Print("Animation Library Cleanup Complete...\n", TextColor::Lightgray);
	}
}

Animation* AnimLibrary::GetAnimation(Type character, const string& clipName)
{
	if (!m_HasBeenSetup)
	{
		Print("Animation Library has not been set up!", TextColor::Red);
		return nullptr;
	}

	map<string, Animation*>::iterator it;

	switch (character)
	{
	case Type::Knight:
		it = m_KnightClips.find(clipName);
		break;
	case Type::Crawlid:
		it = m_CrawlidClips.find(clipName);
		break;
	case Type::Vengefly:
		it = m_VengeflyClips.find(clipName);
		break;
	}

	return it->first.empty() ? nullptr : it->second;
}

void AnimLibrary::PrintInfo(const string& characterName, map<string, Animation*>& dictionary)
{
	// Print Character name and clip number
	Print(characterName, TextColor::Yellow);
	Print(" [" + std::to_string(dictionary.size()) + "]" + '\n', TextColor::Lightgray);

	// Print clip names
	if (!dictionary.empty())
	{
		for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
		{
			if (!it->second->clipName.empty())
			{
				Print(it->second->clipName + '\n', TextColor::Brown);

			}
			else Print(">>Clip not set up<<\n", TextColor::Brown);
		}
	}
}

void AnimLibrary::DeleteClips(map<string, Animation*>& dictionary)
{
	// Delete animations
	for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
		delete it->second;

	// Clean dictionary
	dictionary.clear();
}

void AnimLibrary::KnightSetup()
{
	const auto sprite = SpriteLibrary::GetSprite(SpriteLibrary::Type::Knight);

	auto* currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName		= "Idle";
	currentClip->m_RowPos		= 9;
	currentClip->m_ColumnPos	= 0;
	currentClip->m_NumFrames	= 7;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Walking clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Jumping clip
	currentClip->clipName = "Jumping";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Jumping clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
}

void AnimLibrary::CrawlidSetup()
{
	const auto sprite = SpriteLibrary::GetSprite(SpriteLibrary::Type::Crawlid);

	auto* currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 1;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 2;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 3;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Dead";
	currentClip->m_RowPos = 3;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_CrawlidClips[currentClip->clipName] = currentClip;
}

void AnimLibrary::VengeflySetup()
{
	const auto sprite = SpriteLibrary::GetSprite(SpriteLibrary::Type::Knight);

	auto* currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Flying";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 5;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 1;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 2;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Chasing";
	currentClip->m_RowPos = 3;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*sprite);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 4;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 3;

	m_VengeflyClips[currentClip->clipName] = currentClip;
}