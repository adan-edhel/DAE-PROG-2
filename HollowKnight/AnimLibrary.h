#pragma once
#include <iostream>
#include <map>

struct Animation;

using std::map;
using std::string;

enum class AnimType
{
	Knight,
	Crawlid,
	Vengefly
};

/**
 * \brief Animation Library
 */
class AnimLibrary
{
public:
	static void Setup();
	static void Cleanup();

	static Animation* GetAnimation(AnimType animType, const string& clipName);
	static map<string, Animation*>* GetAnimations(AnimType animType);


private:
	static const bool m_DebugInfo{ true };
	inline static bool m_HasBeenSetup{false};

	inline static map<string, Animation*> m_KnightClips{};
	inline static map<string, Animation*> m_CrawlidClips{};
	inline static map<string, Animation*> m_VengeflyClips{};

	static void PrintInfo(const string& characterName, map<string, Animation*>& dictionary);
	static void DeleteClips(map<string, Animation*>& dictionary);

	static void KnightSetup();
	static void CrawlidSetup();
	static void VengeflySetup();
};