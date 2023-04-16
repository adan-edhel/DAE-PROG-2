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
	Platforms,
	Background,
	Middleground,
	Foreground
};

enum class Font
{
	TrajanPro
};

class SpriteLibrary
{
public:
	static void Setup();
	static void Cleanup();

	static string& GetFont(const Font& type);
	static Texture* GetSprite(const Sprite& type);

private:
	inline static map<Sprite, Texture*> s_Sprites;
	static void Load(const Sprite& type, const string& path);

	inline static map<Font, std::string> s_Fonts;
	static void Load(const Font& type, const string& path);
};

