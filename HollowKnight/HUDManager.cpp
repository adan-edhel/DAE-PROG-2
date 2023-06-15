#include "pch.h"
#include "HUDManager.h"

#include "CORE.h"
#include "GameSettings.h"

HUDManager::HUDManager()
{
}

void HUDManager::UpdatePositionText(const Vector2& position)
{
	if (position != m_PlayerPosition)
	{
		m_PlayerPosition = position;
	}
}

void HUDManager::UpdateHealthBar(const int& health)
{
	for (int i = 0; i < m_AncientMasks.size(); i++)
	{
		m_AncientMasks[i].m_Active = false;
		if (i < health)
		{
			m_AncientMasks[i].m_Active = true;
		}
	}
}

void HUDManager::UIDraw() const
{
	m_FocusBarPtr->Draw(m_FocusBarRect);

	// Draw ancient masks (health)
	for (int i = 0; i < m_AncientMasks.size(); i++)
	{
		const float offsetPosX{m_MasksPositionsOrigin.x + (m_MasksOffset * float(i))};
		m_AncientMasks[i].Draw(Vector2(offsetPosX, m_MasksPositionsOrigin.y));
	}

	// Draw player position
	if (!CORE::s_DebugMode)
	{
		//TODO: Remove for release
		//DrawString(m_PlayerPosition.ToRoundedString(), Vector2(0, -350));
	}
}

void HUDManager::DrawString(const std::string& text, const Vector2 position) const
{
	const Texture m_PositionText{ text, m_Font, m_FontSize, m_FontColor };

	const float drawPosX{ GameSettings::s_ScreenSize.x / 2 - m_PositionText.GetWidth() / 2 };
	const float drawPosY{ GameSettings::s_ScreenSize.y / 2 - m_PositionText.GetHeight() / 2 };

	m_PositionText.Draw(Point2f(drawPosX + position.x ,drawPosY + position.y ));
}
