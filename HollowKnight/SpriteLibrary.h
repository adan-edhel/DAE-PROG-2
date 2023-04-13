#pragma once
#include <map>

class Texture;

using std::map;
using std::string;

enum class Sprite
{
	Default,
	Knight,
	Crawlid,
	Vengelfy,
	Level
};

class SpriteLibrary
{
public:
	static void Setup();
	static void Cleanup();

	static const Texture* GetSprite(const Sprite& type);

private:
	inline static map<Sprite, Texture*> s_Sprites;

	static void LoadSprite(const Sprite& type, const string& path);
};

