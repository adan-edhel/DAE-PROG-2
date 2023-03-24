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
class AnimLibrary
{
public:
	enum class Type
	{
		Knight,
		Crawlid,
		Vengefly
	};

	static void Setup();
	static void Cleanup();

	static Animation* GetAnimation(Type character, const string& clipName);

private:
	static const bool m_DebugInfo{ true };
	inline static bool m_HasBeenSetup{false};

	inline static map<string, Animation*> m_KnightClips;
	inline static map<string, Animation*> m_CrawlidClips;
	inline static map<string, Animation*> m_VengeflyClips;

	static void PrintInfo(const string& characterName, map<string, Animation*>& dictionary);
	static void DeleteClips(map<string, Animation*>& dictionary);

	static void KnightSetup();
	static void CrawlidSetup();
	static void VengeflySetup();
};