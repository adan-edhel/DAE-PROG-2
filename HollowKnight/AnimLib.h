#pragma once
#include "UnityStructs.h"
#include <iostream>
#include <map>

enum class CharacterType;

using std::map;
using std::string;

/**
 * \brief Animation Library
 */
class AnimLib
{
public:
	static void Setup();
	static void Cleanup();

	static Animation* GetAnimation(CharacterType character, const string& clipName);

private:
	static const bool m_DebugInfo{ true };
	inline static bool m_HasBeenSetup{false};

	inline static Texture* m_KnightSheetPtr;
	inline static Texture* m_CrawlidSheetPtr;
	inline static Texture* m_VengeflySheetPtr;

	inline static map<string, Animation*> m_KnightClips;
	inline static map<string, Animation*> m_CrawlidClips;
	inline static map<string, Animation*> m_VengeflyClips;

	static void PrintInfo(const string& characterName, map<string, Animation*>& dictionary);
	static void DeleteClips(map<string, Animation*>& dictionary);

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