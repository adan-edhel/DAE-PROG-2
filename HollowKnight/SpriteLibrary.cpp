#include "pch.h"
#include "SpriteLibrary.h"

#include "Texture.h"

void SpriteLibrary::Setup()
{
	LoadSprite(Sprite::Default, "default_circle.png");
	LoadSprite(Sprite::Knight, "HollowKnight/Knight.png");
	LoadSprite(Sprite::Crawlid, "HollowKnight/Enemies/Crawlid.png");
	LoadSprite(Sprite::Vengelfy, "HollowKnight/Enemies/Vengefly.png");
	LoadSprite(Sprite::Level, "HollowKnight/LevelVisual.png");
}

void SpriteLibrary::Cleanup()
{
	for (auto& sprite : s_Sprites)
	{
		delete sprite.second;
	}
	s_Sprites.clear();
}

const Texture* SpriteLibrary::GetSprite(const Sprite& type)
{
	return s_Sprites.find(type)->second;
}

void SpriteLibrary::LoadSprite(const Sprite& type, const string& path)
{
	s_Sprites[type] = new Texture(path);
}