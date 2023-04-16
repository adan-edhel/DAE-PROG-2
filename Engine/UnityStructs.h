#pragma once
#include "Texture.h"
#include "Vector2.h"

using std::string;

enum class Tag
{
	Default,
	Player,
	Enemy
};

struct Animation
{
	Animation(const string& name, const Texture* sprite, const Vector2& gridCounts, const int& numFrames = 1, const bool& loop = true) :
		m_Name{ name },
		m_NumFrames{ numFrames },
		m_Loop{ loop }
	{
		m_SpriteSize.x = sprite->GetWidth();
		m_SpriteSize.y = sprite->GetHeight();

		m_RowCount = int(gridCounts.x);
		m_ColumnCount = int(gridCounts.y);
	}

	Animation(const string& name, const Texture* sprite, const int& numFrames = 1, const bool& loop = true) :
		Animation(name, sprite, Vector2{ 1,1 }, numFrames, loop)
	{
	}

	void MoveStartFrame(const int& x, const int& y) { MoveStartFrame(Vector2(float(x), float(y))); }
	void MoveStartFrame(const Vector2& index)
	{
		m_RowStartIndex = int(index.x);
		m_ColStartIndex = int(index.y);
	}

	Rectf Update(const float& deltaTime, const float& animSpeed = 1)
	{
		// Calculate the duration of each frame
		const float frameDuration = m_Duration / float(m_NumFrames) / animSpeed;

		// Accumulate time since the last frame change
		m_ElapsedTime += deltaTime;

		// Check if it's time to move to the next frame
		while (m_ElapsedTime >= frameDuration)
		{
			// Move to the next frame
			m_CurrentFrame++;

			// Loop back to the first frame if the end is reached
			if (m_CurrentFrame >= m_NumFrames - 1)
			{
				if (m_Loop)
				{
					m_CurrentFrame = 0;
				}
				else
				{
					m_CurrentFrame = m_NumFrames - 1;
				}
			}

			// Reset the accumulated time
			m_ElapsedTime -= frameDuration;
		}

		return UpdatedSlice();
	}

	const std::string m_Name;

	Vector2 m_SpriteSize;
	int m_RowCount;
	int m_ColumnCount;

	int m_NumFrames;

	int m_RowStartIndex{0};
	int m_ColStartIndex{0};

	int m_CurrentFrame{0};

	float m_Duration{1};
	bool m_Loop{true};

	float m_ElapsedTime{};

private:
	Rectf UpdatedSlice() const
	{
		const int left{m_RowStartIndex + m_CurrentFrame};
		const int top{ m_ColStartIndex + 1};

		//TODO: Check slicing for bugs
		const float sliceWidth = m_SpriteSize.x / float(m_RowCount);
		const float sliceHeight = m_SpriteSize.y / float(m_ColumnCount);

		return Rectf{ left * sliceWidth, top * sliceHeight, sliceWidth, sliceHeight };
	}
};