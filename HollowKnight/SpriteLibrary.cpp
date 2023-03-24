#include "pch.h"
#include "SpriteLibrary.h"

#include "Texture.h"

void SpriteLibrary::Setup()
{
	LoadSprite(Type::Default, "default_circle.png");
	LoadSprite(Type::Knight, "HollowKnight/Knight.png");
	LoadSprite(Type::Crawlid, "HollowKnight/Enemies/Crawlid.png");
	LoadSprite(Type::Vengelfy, "HollowKnight/Enemies/Vengefly.png");
}

void SpriteLibrary::Cleanup()
{
	for (auto& sprite : s_Sprites)
	{
		delete sprite.second;
	}
	s_Sprites.clear();
}

const Texture* SpriteLibrary::GetSprite(const Type& type)
{
	return s_Sprites.find(type)->second;
}

void SpriteLibrary::LoadSprite(const Type& type, const string& path)
{
	s_Sprites[type] = new Texture(path);
}