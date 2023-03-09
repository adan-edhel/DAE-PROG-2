#include "pch.h"
#include <iostream>
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	SpriteRenderer::SpriteRenderer(const std::string& spritePath) :
		m_Sprite{ new Texture(spritePath) }
	{

	}

	void SpriteRenderer::Draw() const
	{

	}

	void SpriteRenderer::Update(const float& deltaTime)
	{

	}

	bool SpriteRenderer::IsFlipped() const { return m_isFlipped; }

	Vector2 SpriteRenderer::Bounds() const
	{
		if (m_Sprite != nullptr)
		{
			return Vector2(m_Sprite->GetWidth(), m_Sprite->GetHeight());
		}
		std::cout << ">>Warning<< No sprite has been loaded.\n";
		return Vector2{};
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete m_Sprite;
	}
}