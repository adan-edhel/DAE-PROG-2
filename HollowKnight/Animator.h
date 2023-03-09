#pragma once
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	class Animator : public IComponent
	{
	private:
		SpriteRenderer* m_SpriteRenderer;

	public:
		Animator(SpriteRenderer& renderer);

		struct Animation
		{
			int m_RowPosition;
			int m_ColumnPosition;
			int m_NumberOfFrames;
			bool m_Loop;

			Animation(int rowPosition, int columnPosition, int numberOfFrames, bool loop = false) :
			m_RowPosition{rowPosition},
			m_ColumnPosition{columnPosition},
			m_NumberOfFrames{numberOfFrames},
			m_Loop{loop}
			{
				
			}

			Animation(int rowPosition, int columnPosition) :
			Animation(rowPosition, columnPosition, 1)
			{
				
			}
		};
	};
}

