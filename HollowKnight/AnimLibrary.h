#pragma once
#include "UnityStructs.h"
#include <iostream>
#include <map>

enum class CharacterType;

class AnimLibrary
{
public:
	static void Setup();
	static void Cleanup();

	static Animation* GetAnimation(CharacterType actor, const std::string& clipName);

private:
	static Texture* m_KnightSheetPtr;
	static Texture* m_CrawlidSheetPtr;
	static Texture* m_VengeflySheetPtr;

	static std::map<Animation*, std::string> m_knightClips;
	static std::map<Animation*, std::string> m_CrawlidClips;
	static std::map<Animation*, std::string> m_VengeflyClips;

	static void KnightSetup();
	static void CrawlidSetup();
	static void VengeflySetup();
};

enum class CharacterType
{
	Knight,
	Crawlid,
	Vengefly
};