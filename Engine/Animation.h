#pragma once
#include "Texture.h"
#include "Vector2.h"

using std::string;

struct Animation
{
	const std::string m_Name;
	float m_FrameDuration;
	bool m_Loop;

	Animation(const string& name, const Texture* sprite, const Vector2& gridCounts, const int& numFrames = 1, const float& m_FrameDuration = 0.15f, const bool& loop = true) :
		m_Name{ name },
		m_FrameDuration{m_FrameDuration},
		m_Loop{ loop },
		m_NumFrames{ numFrames }
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

	/*
	Animation(const Animation& other) : // Copy constructor
		m_Name(other.m_Name),
		m_FrameDuration(other.m_FrameDuration),
		m_Loop(other.m_Loop),
		m_NumFrames(other.m_NumFrames),
		m_RowCount(other.m_RowCount),
		m_ColumnCount(other.m_ColumnCount),
		m_SpriteSize(other.m_SpriteSize),
		m_CurrentFrame(other.m_CurrentFrame),
		m_StartPosIndex(other.m_StartPosIndex),
		m_FinishedPlaying(other.m_FinishedPlaying),
		m_ElapsedTime(other.m_ElapsedTime)
	{
	} 
	Animation& operator=(const Animation& other) // Copy Operator
	{
		if (this != &other)
		{
			m_Name = other.m_Name;
			m_FrameDuration = other.m_FrameDuration;
			m_Loop = other.m_Loop;
			m_NumFrames = other.m_NumFrames;
			m_RowCount = other.m_RowCount;
			m_ColumnCount = other.m_ColumnCount;
			m_SpriteSize = other.m_SpriteSize;
			m_CurrentFrame = other.m_CurrentFrame;
			m_StartPosIndex = other.m_StartPosIndex;
			m_FinishedPlaying = other.m_FinishedPlaying;
			m_ElapsedTime = other.m_ElapsedTime;
		}
		return *this;
	}
	*/

	void MoveStartFrame(const int& x, const int& y) { MoveStartFrame(Vector2(float(x), float(y))); }
	void MoveStartFrame(Vector2 index)
	{
		m_StartPosIndex.x = index.x;
		m_StartPosIndex.y = index.y;
	}

	Vector2 GridSize() const { return Vector2(m_RowCount, m_ColumnCount); }
	bool Finished() const { return m_FinishedPlaying; }
	int FrameCount() const { return m_NumFrames; }
	float Length() const { return m_FrameDuration * m_NumFrames; }

	Rectf Update(const float& deltaTime, const float& animSpeed = 1) //TODO: fix last frame skipping
	{
		// Calculate the duration of each frame
		m_FrameDuration *= animSpeed;

		// Accumulate time since the last frame change
		m_ElapsedTime += deltaTime;

		// Check if it's time to move to the next frame
		if (m_ElapsedTime >= m_FrameDuration)
		{
			// Move to the next frame
			m_CurrentFrame++;

			// Loop back to the first frame if the end is reached
			if (m_CurrentFrame >= m_NumFrames - 1)
			{
				m_FinishedPlaying = true;

				if (m_Loop)
				{
					m_CurrentFrame = 0;
					m_FinishedPlaying = false;
				}
				else
				{
					m_CurrentFrame = m_NumFrames - 1;
				}
			}

			// Reset the accumulated time
			m_ElapsedTime -= m_FrameDuration;
		}

		return UpdatedSlice();
	}

	// Reset animation
	void Reset()
	{
		m_ElapsedTime = 0;
		m_CurrentFrame = 0;
	}

private:
	int m_NumFrames;

	int m_RowCount;
	int m_ColumnCount;
	Vector2 m_SpriteSize;

	int m_CurrentFrame{0};
	Vector2 m_StartPosIndex{1,1};

	bool m_FinishedPlaying;
	float m_ElapsedTime{};

	Rectf UpdatedSlice() const
	{
		//TODO: Double-Check slicing for bugs

		const int left{(int(m_StartPosIndex.x) - 1) + m_CurrentFrame};
		const int top {(int(m_StartPosIndex.y) - 1) + 1};

		const float sliceWidth = m_SpriteSize.x / float(m_RowCount);
		const float sliceHeight = m_SpriteSize.y / float(m_ColumnCount);

		return Rectf{ float(left) * sliceWidth, float(top) * sliceHeight, sliceWidth, sliceHeight };
	}
};