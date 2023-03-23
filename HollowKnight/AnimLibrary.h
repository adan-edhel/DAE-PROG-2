#pragma once
#include "UnityStructs.h"
#include <iostream>
#include <map>

enum class CharacterType;

using std::map;
using std::string;

class AnimLibrary
{
public:
	static void Setup();
	static void Cleanup();

	static Animation* GetAnimation(CharacterType character, const string& clipName);

private:
	static Texture* m_KnightSheetPtr;
	static Texture* m_CrawlidSheetPtr;
	static Texture* m_VengeflySheetPtr;

	static map<string, Animation*> m_KnightClips;
	static map<string, Animation*> m_CrawlidClips;
	static map<string, Animation*> m_VengeflyClips;

	static void PrintInfo(const string& characterName, map<string, Animation*>& dictionary);

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