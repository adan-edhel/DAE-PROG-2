#include "pch.h"
#include "AnimLibrary.h"

#include "AmrothUtils.h"
#include "GameSettings.h"

Texture* AnimLibrary::m_KnightSheetPtr;
Texture* AnimLibrary::m_CrawlidSheetPtr;
Texture* AnimLibrary::m_VengeflySheetPtr;

map<string, Animation*> AnimLibrary::m_KnightClips;
map<string, Animation*> AnimLibrary::m_CrawlidClips;
map<string, Animation*> AnimLibrary::m_VengeflyClips;

void AnimLibrary::Setup()
{
	m_KnightSheetPtr = new Texture("HollowKnight/Knight.png");
	m_CrawlidSheetPtr = new Texture("HollowKnight/Enemies/Crawlid.png");
	m_VengeflySheetPtr = new Texture("HollowKnight/Enemies/Vengefly.png");

	KnightSetup();
	CrawlidSetup();
	VengeflySetup();

	// Print information in the console
	if (GameSettings::s_DebugMode) 
	{
		Print("############## Animation Library ##############\n", TextColor::Darkgray);

		//TODO: Test animation clips
		Print("--Animations aren't yet implemented--\n", TextColor::LightcyaN);

		PrintInfo("Hollow Knight", m_KnightClips);
		PrintInfo("Crawlid", m_CrawlidClips);
		PrintInfo("Vengefly", m_VengeflyClips);

		Print("###############################################\n", TextColor::Darkgray);
	}
}

void AnimLibrary::Cleanup()
{
	map<string, Animation*>::iterator it;

	for (it = m_KnightClips.begin(); it != m_KnightClips.end(); ++it)
		delete it->second;

	for (it = m_CrawlidClips.begin(); it != m_CrawlidClips.end(); ++it)
		delete it->second;

	for (it = m_VengeflyClips.begin(); it != m_VengeflyClips.end(); ++it)
		delete it->second;

	m_KnightClips.clear();
	m_CrawlidClips.clear();
	m_VengeflyClips.clear();

	delete m_KnightSheetPtr;
	delete m_CrawlidSheetPtr;
	delete m_VengeflySheetPtr;
}

Animation* AnimLibrary::GetAnimation(CharacterType character, const string& clipName)
{
	map<string, Animation*>::iterator it;

	switch (character)
	{
	case CharacterType::Knight:
		it = m_KnightClips.find(clipName);
		break;
	case CharacterType::Crawlid:
		it = m_CrawlidClips.find(clipName);
		break;
	case CharacterType::Vengefly:
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

void AnimLibrary::KnightSetup()
{
	auto* currentClip = new Animation(*m_KnightSheetPtr);

	// Idle clip
	currentClip->clipName		= "Idle";
	currentClip->m_RowPos		= 9;
	currentClip->m_ColumnPos	= 0;
	currentClip->m_NumFrames	= 7;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Walking clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Jumping clip
	currentClip->clipName = "Jumping";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Jumping clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_KnightClips[currentClip->clipName] = currentClip;
}

void AnimLibrary::CrawlidSetup()
{
	auto* currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 1;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 2;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 3;

	m_CrawlidClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Dead";
	currentClip->m_RowPos = 3;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_CrawlidClips[currentClip->clipName] = currentClip;
}

void AnimLibrary::VengeflySetup()
{
	auto* currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Flying";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 5;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 1;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 2;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 2;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Chasing";
	currentClip->m_RowPos = 3;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 4;

	m_VengeflyClips[currentClip->clipName] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 4;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 3;

	m_VengeflyClips[currentClip->clipName] = currentClip;
}