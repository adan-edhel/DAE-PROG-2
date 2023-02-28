#include "pch.h"
#include "Sprite2D.h"

// MAKE THIS START FROM TOP OF THE SPRITESHEET

Sprite2D::Sprite2D(const std::string& textureDirectory, const int& frames, const int& columns, const int& rows, const float& scale) :
	m_Texture{ textureDirectory },
	m_Frames(frames),
	m_Columns(columns),
	m_Rows(rows),
	m_Scale(scale)
{
	m_FrameSize = m_Texture.GetWidth() / m_Columns;
}

Sprite2D::Sprite2D(const std::string& textureDirectory) :
Sprite2D(textureDirectory, 1, 1, 1)
{
}

void Sprite2D::Update(const float& elapsedSec)
{
	// If not an animation, return
	if (m_Frames <= 1) return;

	// Increment accumulated time
	m_AccumulatedTimeInSeconds += elapsedSec;

	// Calculate number of frame iterations
	const int iteration{ int(m_AccumulatedTimeInSeconds / AnimationSpeed) };

	// Determine the current frame iteration within the range of the total number of frames
	const int currentFrame = iteration % m_Frames;

	// Determine the position of the current frame
	m_FrameIndex.y = currentFrame / m_Columns;
	m_FrameIndex.x = currentFrame % m_Columns;

	// Account for the last row having fewer columns
	if (currentFrame >= (m_Frames - m_Columns))
	{
		m_FrameIndex.x = (currentFrame - (m_Frames - m_Columns)) % m_Columns;
		m_FrameIndex.y = m_Rows - 1;
	}
}

void Sprite2D::Draw() const
{
	// Position & size to draw
	const float scaledSize{ m_FrameSize * m_Scale };
	const Rectf dimensionRect{ 0, 0, scaledSize, scaledSize };

	// Position & size within spritesheet
	Rectf slicedRect{ 0, 0, m_FrameSize, m_FrameSize };

	// Position slice
	slicedRect.left = float(m_FrameIndex.x) * m_FrameSize;
	slicedRect.bottom = m_Texture.GetHeight() - float(m_FrameIndex.y) * m_FrameSize;

	// Draw slice
	m_Texture.Draw(dimensionRect, slicedRect);
}

void Sprite2D::End() const
{
	delete this;
}