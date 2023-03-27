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

	Animation(const Texture& sprite, int numFrames, int columns, int rows) :
		m_pSprite{&sprite}
	{
	}

	Animation(const Texture& sprite) :
		Animation(sprite, 1, 1, 1)
	{
	}

	const Texture* m_pSprite;

	int m_NumFrames;

	int m_RowPos;
	int m_ColumnPos;

	int m_CurrentFrame{1};

	float m_FrameDuration{1};
	bool m_Loop{true};

	float m_AccumulatedTime{};

	void Update(const float& deltaTime)
	{
		// Only update the animation if there is more than 1 frame
		if (m_NumFrames <= 1) return;

		// Accumulate time since the last frame change
		m_AccumulatedTime += deltaTime;

		// Check if it's time to move to the next frame
		if (m_AccumulatedTime >= m_FrameDuration)
		{
			// Reset the accumulated time
			m_AccumulatedTime -= m_FrameDuration;

			// Move to the next frame
			m_CurrentFrame++;

			// Loop back to the first frame if the end is reached
			if (m_CurrentFrame > m_NumFrames)
			{
				if (m_Loop)
				{
					m_CurrentFrame = 1;
				}
				else
				{
					m_CurrentFrame = m_NumFrames;
				}
			}
		}

		// Calculate the row and column positions of the current frame
		m_RowPos = (m_CurrentFrame - 1) / m_ColumnPos;
		m_ColumnPos = (m_CurrentFrame - 1) & m_ColumnPos;
	}
};