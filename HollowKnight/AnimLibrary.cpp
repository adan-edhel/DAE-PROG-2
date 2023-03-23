#include "pch.h"
#include "AnimLibrary.h"

#include "AmrothUtils.h"
#include "GameSettings.h"

Texture* AnimLibrary::m_KnightSheetPtr;
Texture* AnimLibrary::m_CrawlidSheetPtr;
Texture* AnimLibrary::m_VengeflySheetPtr;

std::map<Animation*, std::string> AnimLibrary::m_knightClips;
std::map<Animation*, std::string> AnimLibrary::m_CrawlidClips;
std::map<Animation*, std::string> AnimLibrary::m_VengeflyClips;

void AnimLibrary::Setup()
{
	m_KnightSheetPtr = new Texture("HollowKnight/Knight.png");
	m_CrawlidSheetPtr = new Texture("HollowKnight/Enemies/Crawlid.png");
	m_VengeflySheetPtr = new Texture("HollowKnight/Enemies/Vengefly.png");

	KnightSetup();
	CrawlidSetup();
	VengeflySetup();

	if (GameSettings::debugMode)
	{
		Print("############## Animation Library ##############\n", TextColor::Darkgray);

		Print("--Animations aren't yet implemented--\n", TextColor::LightcyaN);

		std::map<Animation*, std::string>::iterator it;

		Print("Hollow Knight ", TextColor::Yellow);
		Print("[" + std::to_string(m_knightClips.size()) + "]" + '\n', TextColor::Lightgray);

		for (it = m_knightClips.begin(); it != m_knightClips.end(); ++it)
			Print(it->first->clipName + '\n', TextColor::Brown);

		Print("Crawlid ", TextColor::Yellow);
		Print("[" + std::to_string(m_CrawlidClips.size()) + "]" + '\n', TextColor::Lightgray);

		for (it = m_CrawlidClips.begin(); it != m_CrawlidClips.end(); ++it)
			Print(it->first->clipName + '\n', TextColor::Brown);

		Print("Vengefly ", TextColor::Yellow);
		Print("[" + std::to_string(m_VengeflyClips.size()) + "]" + '\n', TextColor::Lightgray);

		for (it = m_VengeflyClips.begin(); it != m_VengeflyClips.end(); ++it)
			Print(it->first->clipName + '\n', TextColor::Brown);
		Print("###############################################\n", TextColor::Darkgray);
	}
}

Animation* AnimLibrary::GetAnimation(CharacterType actor, const std::string& clipName)
{
	std::map<Animation*, std::string>::iterator it;

	switch (actor)
	{
	case CharacterType::Knight:
		for (it = m_knightClips.begin(); it != m_knightClips.end(); ++it)
			if (it->second == clipName)
				return it->first;
		break;
	case CharacterType::Crawlid:
		for (it = m_CrawlidClips.begin(); it != m_CrawlidClips.end(); ++it)
			if (it->second == clipName)
				return it->first;
		break;
	case CharacterType::Vengefly:
		for (it = m_VengeflyClips.begin(); it != m_VengeflyClips.end(); ++it)
			if (it->second == clipName)
				return it->first;
		break;
	}

	Print("Animation clip doesn't exist.\n");
	return nullptr;
}

void AnimLibrary::KnightSetup()
{
	auto* currentClip = new Animation(*m_KnightSheetPtr);

	// Idle clip
	currentClip->clipName		= "Idle";
	currentClip->m_RowPos		= 9;
	currentClip->m_ColumnPos	= 0;
	currentClip->m_NumFrames	= 7;

	m_knightClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Walking clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_knightClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Jumping clip
	currentClip->clipName = "Jumping";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_knightClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_KnightSheetPtr);

	// Jumping clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 0;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 9;

	m_knightClips[currentClip] = currentClip->clipName;
}

void AnimLibrary::CrawlidSetup()
{
	auto* currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Walking";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_CrawlidClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_CrawlidClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_CrawlidClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_CrawlidSheetPtr);

	// Idle clip
	currentClip->clipName = "Dead";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_CrawlidClips[currentClip] = currentClip->clipName;
}

void AnimLibrary::VengeflySetup()
{
	auto* currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Flying";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_VengeflyClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Turning";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_VengeflyClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Attacking";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_VengeflyClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Charging";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_VengeflyClips[currentClip] = currentClip->clipName;
	// ----------------------------------------------
	currentClip = new Animation(*m_VengeflySheetPtr);

	// Idle clip
	currentClip->clipName = "Dying";
	currentClip->m_RowPos = 9;
	currentClip->m_ColumnPos = 0;
	currentClip->m_NumFrames = 7;

	m_VengeflyClips[currentClip] = currentClip->clipName;
}

void AnimLibrary::Cleanup()
{
	std::map<Animation*, std::string>::iterator it;

	for (it = m_knightClips.begin(); it != m_knightClips.end(); ++it)
			delete it->first;

	for (it = m_CrawlidClips.begin(); it != m_CrawlidClips.end(); ++it)
		delete it->first;

	for (it = m_VengeflyClips.begin(); it != m_VengeflyClips.end(); ++it)
		delete it->first;

	m_knightClips.clear();
	m_CrawlidClips.clear();
	m_VengeflyClips.clear();

	delete m_KnightSheetPtr;
	delete m_CrawlidSheetPtr;
	delete m_VengeflySheetPtr;
}