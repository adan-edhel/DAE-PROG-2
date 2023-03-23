#pragma once
#include "Texture.h"

enum class Tag
{
	Default,
	Player,
	Enemy
};

struct Animation
{
	std::string clipName;

	Animation(Texture& sprite, int numFrames, int columns, int rows) :
		m_pSprite{&sprite}
	{
		
	}

	Animation(Texture& sprite) :
		Animation(sprite, 1, 1, 1)
	{
		
	}

	Texture* m_pSprite;

	int m_CurrentFrame{1};
	int m_NumFrames;

	int m_RowPos;
	int m_ColumnPos;

	float m_FrameDuration{1};
	bool m_Loop{true};

	float m_AccumulatedTime{};

	void Update(const float& deltaTime)
	{
		m_AccumulatedTime += deltaTime;

		const int iteration{ int(m_AccumulatedTime / m_FrameDuration) };

		m_CurrentFrame = iteration % m_NumFrames;
	}


	//Animation(Texture& sprite, ) :
	//m_pSprite{&sprite},
	//m_RowPos{ rowPosition },
	//m_ColumnPos{ columnPosition },
	//m_NumFrames{ numberOfFrames },
	//m_Loop{ loop }
	//{

	//}

	//Animation(int rowPosition, int columnPosition) :
	//	Animation(rowPosition, columnPosition, 1)
	//{

	//}
};