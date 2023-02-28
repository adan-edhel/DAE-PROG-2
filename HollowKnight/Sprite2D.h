#pragma once
#include "Texture.h"
#include "Vector2.h"

class Sprite2D
{
public:
	Sprite2D(const std::string& textureDirectory,
		const int& frames,
		const int& columns,
		const int& rows,
		const float& scale = 1.0f);
	Sprite2D(const std::string& textureDirectory);

private:
	Texture m_Texture;

	float m_AccumulatedTimeInSeconds{};
	Vector2 m_FrameIndex{};
	float m_FrameSize{};

	const int m_Frames;
	const int m_Columns;
	const int m_Rows;
	float m_Scale;

	float AnimationSpeed{0.15f}; // Move to SpriteRenderer

	void Update(const float& elapsedSec);
	void Draw() const;
	void End() const;
};
