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
	Texture* m_pSprite;

	int m_NumFrames;

	int m_RowPos;
	int m_ColumnPos;

	int m_CurrentFrame;
	float m_FrameDuration;
	bool m_Loop;


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