#pragma once
#include <map>

class Texture;

using std::map;
using std::string;

enum class Sprite
{
	// Game
	Default,
	Knight,
	Crawlid,
	Vengelfy,
	Platforms,
	Background,
	Middleground,
	Foreground,

	//Misc
	Coin,

	// HUD
	AncientMask,
	FocusBar,

	// Menu
	MenuBackground,
	MenuTitle
};

enum class Font
{
	TrajanPro
};

class SpriteLibrary final
{
public:
	SpriteLibrary();
	~SpriteLibrary();
	SpriteLibrary(const SpriteLibrary& other) = delete;					// copy constructor
	SpriteLibrary(SpriteLibrary&& other) noexcept = delete;				// move constructor
	SpriteLibrary& operator=(const SpriteLibrary& other) = delete;		// copy operator
	SpriteLibrary& operator=(SpriteLibrary&& other) noexcept = delete;	// move operator

	static string& GetFont(const Font& type);
	static Texture* GetSprite(const Sprite& type);

private:
	inline static map<Sprite, Texture*> s_Sprites;
	static void Load(const Sprite& type, const string& path);

	inline static map<Font, std::string> s_Fonts;
	static void Load(const Font& type, const string& path);
};

