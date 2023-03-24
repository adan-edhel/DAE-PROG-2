#pragma once
#include <map>

class Texture;

using std::map;
using std::string;

class SpriteLibrary
{
public:
	enum class Type
	{
		Default,
		Knight,
		Crawlid,
		Vengelfy
	};

	static void Setup();
	static void Cleanup();

	static const Texture* GetSprite(const Type& type);

private:
	inline static map<Type, Texture*> s_Sprites;

	static void LoadSprite(const Type& type, const string& path);
};

