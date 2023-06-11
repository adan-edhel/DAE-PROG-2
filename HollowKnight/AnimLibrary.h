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
class AnimLibrary final
{
public:
	AnimLibrary();
	~AnimLibrary();
	AnimLibrary(const AnimLibrary& other) = delete;					// copy constructor
	AnimLibrary(AnimLibrary&& other) noexcept = delete;				// move constructor
	AnimLibrary& operator=(const AnimLibrary& other) = delete;		// copy operator
	AnimLibrary& operator=(AnimLibrary&& other) noexcept = delete;	// move operator

	static Animation* GetAnimation(AnimType animType, const string& clipName);
	static map<string, Animation*>* GetAnimations(AnimType animType);

private:
	static const bool m_DebugInfo{ true };

	inline static map<string, Animation*> m_KnightClips{};
	inline static map<string, Animation*> m_CrawlidClips{};
	inline static map<string, Animation*> m_VengeflyClips{};

	static void PrintInfo(const string& characterName, map<string, Animation*>& dictionary);
	static void DeleteClips(map<string, Animation*>& dictionary);

	static void KnightSetup();
	static void CrawlidSetup();
	static void VengeflySetup();
};