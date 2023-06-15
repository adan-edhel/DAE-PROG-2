#include "pch.h"
#include "AnimLibrary.h"

#include "CORE.h"
#include <Animation.h>
#include "AmrothUtils.h"
#include "SpriteLibrary.h"

AnimLibrary::AnimLibrary()
{
	if (CORE::s_DebugMode)
	{
		Print("Animation Library Being Setup...\n", TextColor::Lightgray);
	}

	KnightSetup();
	CrawlidSetup();
	VengeflySetup();

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

AnimLibrary::~AnimLibrary()
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
	{
		delete it->second;
	}

	// Clean dictionary
	dictionary.clear();
}

void AnimLibrary::KnightSetup()
{
	const Texture* sprite = SpriteLibrary::GetSprite(Sprite::Knight);
	const Vector2 gridCount{ 12,12 };

	Animation* currentClip = new Animation("Idle", sprite, gridCount, 1);
	currentClip->MoveStartFrame(Vector2(1, 9));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Walk", sprite, gridCount, 6);
	currentClip->MoveStartFrame(Vector2(7, 7));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Jump", sprite, gridCount, 4, 0.2f, false);
	currentClip->MoveStartFrame(Vector2(2, 10));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Fall", sprite, gridCount, 1, .2f, false);
	currentClip->MoveStartFrame(Vector2(6, 10));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Attack1", sprite, gridCount, 3, .08f, false);
	currentClip->MoveStartFrame(Vector2(1, 5));
	m_KnightClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Attack2", sprite, gridCount, 3, .08f, false);
	currentClip->MoveStartFrame(Vector2(4, 5));
	m_KnightClips[currentClip->m_Name] = currentClip;
}

void AnimLibrary::CrawlidSetup()
{
	const Texture* sprite = SpriteLibrary::GetSprite(Sprite::Crawlid);
	const Vector2 gridCount{ 4,4 };

	Animation* currentClip = new Animation("Walk", sprite, gridCount, 4);
	currentClip->MoveStartFrame(Vector2(1, 1));
	m_CrawlidClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Turn", sprite, gridCount, 2, .15f, false);
	currentClip->MoveStartFrame(Vector2(1, 2));
	m_CrawlidClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
		// ----------------------------------------------
	currentClip = new Animation("Die", sprite, gridCount, 3, .15f, false);
	currentClip->MoveStartFrame(Vector2(1, 3));
	m_CrawlidClips[currentClip->m_Name] = currentClip;
}

void AnimLibrary::VengeflySetup()
{
	const Texture* sprite = SpriteLibrary::GetSprite(Sprite::Vengelfy);
	const Vector2 gridCount{ 5,5 };

	Animation* currentClip = new Animation("Fly", sprite, gridCount, 5, .15f, true);
	currentClip->MoveStartFrame(Vector2(1, 1));
	m_VengeflyClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Turn", sprite, gridCount, 2, .15f, false);
	currentClip->MoveStartFrame(Vector2(1, 2));
	m_VengeflyClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Startle", sprite, gridCount, 4, .15f, false);
	currentClip->MoveStartFrame(Vector2(1, 3));
	m_VengeflyClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Charge", sprite, gridCount, 4, .15f, true);
	currentClip->MoveStartFrame(Vector2(1, 4));
	m_VengeflyClips[currentClip->m_Name] = currentClip;
	// ----------------------------------------------
	currentClip = new Animation("Die", sprite, gridCount, 3, .15f, false);
	currentClip->MoveStartFrame(Vector2(1, 5));
	m_VengeflyClips[currentClip->m_Name] = currentClip;
}