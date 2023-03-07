#include "pch.h"
#include <iostream>
#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer()
{

}

Vector2 SpriteRenderer::Bounds() const
{
	if (m_Sprite != nullptr)
	{
		return Vector2(m_Sprite->GetWidth(), m_Sprite->GetHeight());
	}
	std::cout << ">>Warning<< No sprite has been loaded.\n";
	return Vector2{};
}

void SpriteRenderer::Draw() const
{
	
}

void SpriteRenderer::Update(const float& deltaTime)
{
	
}
SpriteRenderer::~SpriteRenderer()
{
	delete m_Sprite;
}