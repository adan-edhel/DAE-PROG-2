#include "pch.h"
#include "SpriteLibrary.h"

#include "Texture.h"

void SpriteLibrary::Setup()
{
	// Game
	Load(Sprite::Default, "default_circle.png");
	Load(Sprite::Knight, "HollowKnight/Knight.png");
	Load(Sprite::Crawlid, "HollowKnight/Enemies/Crawlid.png");
	Load(Sprite::Vengelfy, "HollowKnight/Enemies/Vengefly.png");
	Load(Sprite::Platforms, "HollowKnight/Environment/Platforms.png");
	Load(Sprite::Background, "HollowKnight/Environment/Background.png");
	Load(Sprite::Middleground, "HollowKnight/Environment/Middleground.png");

	// HUD
	Load(Sprite::AncientMask, "HollowKnight/HUD/AncientMask.png");
	Load(Sprite::FocusBar, "HollowKnight/HUD/FocusBar.png");

	// Menu
	Load(Sprite::Foreground, "HollowKnight/Environment/Foreground.png");
	Load(Sprite::MenuBackground, "HollowKnight/Menu/Background.png");
	Load(Sprite::MenuTitle, "HollowKnight/Menu/Title.png");

	Load(Font::TrajanPro, "Trajan Pro Regular.ttf");
}

void SpriteLibrary::Cleanup()
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