#include "pch.h"
#include "AnimLibrary.h"

#include "CORE.h"
#include <Animation.h>
#include "AmrothUtils.h"
#include "SpriteLibrary.h"

//TODO: Test animation clips

void AnimLibrary::Setup()
{
	if (CORE::s_DebugMode)
	{
		Print("Animation Library Being Setup...\n", TextColor::Lightgray);
	}

	KnightSetup();
	CrawlidSetup();
	VengeflySetup();

	m_HasBeenSetup = true;

	// Print information in the console
	if (CORE::s_DebugMode && m_DebugInfo)
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

	if (CORE::s_DebugMode)
	{
		Print("Animation Library Cleanup Complete...\n", TextColor::Lightgray);
	}
}

Animation* AnimLibrary::GetAnimation(AnimType animType, const string& clipName)
{
	if (!m_HasBeenSetup)
	{
		Print("Animation Library has not been set up!", TextColor::Red);
		return nullptr;
	}

	map<string, Animation*>::iterator it;

	switch (animType)
	{
	case AnimType::Knight:
		it = m_KnightClips.find(clipName);
		break;
	case AnimType::Crawlid:
		it = m_CrawlidClips.find(clipName);
		break;
	case AnimType::Vengefly:
		it = m_VengeflyClips.find(clipName);
		break;
	}

	return it->first.empty() ? nullptr : it->second;
}

map<string, Animation*>* AnimLibrary::GetAnimations(AnimType animType)
{
	switch (animType)
	{
		case AnimType::Knight:
			return &m_KnightClips;
		case AnimType::Crawlid:
			return &m_CrawlidClips;
		case AnimType::Vengefly: 
			return &m_VengeflyClips;
	}
	return nullptr;
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
			if (!it->second->m_Name.empty())
			{
				Print(it->second->m_Name + '\n', TextColor::Brown);

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
	const auto* sprite = SpriteLibrary::GetSprite(Sprite::Knight);
	const Vector2 gridCount{ 12,12 };

	auto* currentClip = new Animation("Idle", sprite, gridCount, 7);
	currentClip->MoveStartFrame(Vector2(1, 9));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Walk", sprite, gridCount, 6);
	currentClip->MoveStartFrame(Vector2(7, 7));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Jump", sprite, gridCount, 4, false);
	currentClip->MoveStartFrame(Vector2(2, 10));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Fall", sprite, gridCount, 3, false);
	currentClip->MoveStartFrame(Vector2(6, 10));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Attack1", sprite, gridCount, 3, false);
	currentClip->MoveStartFrame(Vector2(1, 5));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Attack2", sprite, gridCount, 3, false);
	currentClip->MoveStartFrame(Vector2(4, 5));
	m_KnightClips[currentClip->m_Name] = currentClip;
}

void AnimLibrary::CrawlidSetup()
{
	//const auto sprite = SpriteLibrary::GetSprite(Sprite::Crawlid);

	//auto* currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Walking";
	//currentClip->m_RowStartIndex = 0;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 4;

	//m_CrawlidClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Turning";
	//currentClip->m_RowStartIndex = 1;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 2;

	//m_CrawlidClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Dying";
	//currentClip->m_RowStartIndex = 2;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 3;

	//m_CrawlidClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Dead";
	//currentClip->m_RowStartIndex = 3;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 2;

	//m_CrawlidClips[currentClip->m_Name] = currentClip;
}

void AnimLibrary::VengeflySetup()
{
	//const auto sprite = SpriteLibrary::GetSprite(Sprite::Knight);

	//auto* currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Flying";
	//currentClip->m_RowStartIndex = 0;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 5;

	//m_VengeflyClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Turning";
	//currentClip->m_RowStartIndex = 1;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 2;

	//m_VengeflyClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Attacking";
	//currentClip->m_RowStartIndex = 2;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 4;

	//m_VengeflyClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Chasing";
	//currentClip->m_RowStartIndex = 3;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 4;

	//m_VengeflyClips[currentClip->m_Name] = currentClip;
	//// ----------------------------------------------
	//currentClip = new Animation();

	//// Idle clip
	//currentClip->m_Name = "Dying";
	//currentClip->m_RowStartIndex = 4;
	//currentClip->m_ColStartIndex = 0;
	//currentClip->m_NumFrames = 3;

	//m_VengeflyClips[currentClip->m_Name] = currentClip;
}