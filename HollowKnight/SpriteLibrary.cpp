#include "pch.h"
#include "SpriteLibrary.h"

#include "Texture.h"

SpriteLibrary::SpriteLibrary()
{
	// Game
	Load(Sprite::Default, "Default/default_circle.png");
	Load(Sprite::Knight, "Actors/Knight.png");
	Load(Sprite::Crawlid, "Actors/Crawlid.png");
	Load(Sprite::Vengelfy, "Actors/Vengefly.png");
	Load(Sprite::Platforms, "Environment/Platforms.png");
	Load(Sprite::Background, "Environment/Background.png");
	Load(Sprite::Middleground, "Environment/Middleground.png");
	Load(Sprite::Foreground, "Environment/Foreground.png");

	//Misc
	Load(Sprite::Coin, "HUD/Coin.png");

	// HUD
	Load(Sprite::AncientMask, "HUD/AncientMask.png");
	Load(Sprite::FocusBar, "HUD/FocusBar.png");

	// Menu
	Load(Sprite::MenuBackground, "Menu/Background.png");
	Load(Sprite::MenuTitle, "Menu/Title.png");

	Load(Font::TrajanPro, "Fonts/Trajan Pro Regular.ttf");
}

SpriteLibrary::~SpriteLibrary()
{
	for (const auto& sprite : s_Sprites)
	{
		delete sprite.second;
	}
	s_Sprites.clear();
	s_Fonts.clear();
}

string& SpriteLibrary::GetFont(const Font& type)
{
	return s_Fonts.find(type)->second;
}

Texture* SpriteLibrary::GetSprite(const Sprite& type)
{
	return s_Sprites.find(type)->second;
}

void SpriteLibrary::Load(const Sprite& type, const string& path)
{
	s_Sprites[type] = new Texture(path);
}

void SpriteLibrary::Load(const Font& type, const string& path)
{
	s_Fonts[type] = path;
}