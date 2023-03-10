#pragma once

enum class Tag
{
	Default,
	Player,
	Enemy
};

struct Animation
{
	int m_RowPosition;
	int m_ColumnPosition;
	int m_NumberOfFrames;
	bool m_Loop;

	Animation(int rowPosition, int columnPosition, int numberOfFrames, bool loop = false) :
		m_RowPosition{ rowPosition },
		m_ColumnPosition{ columnPosition },
		m_NumberOfFrames{ numberOfFrames },
		m_Loop{ loop }
	{

	}

	Animation(int rowPosition, int columnPosition) :
		Animation(rowPosition, columnPosition, 1)
	{

	}
};