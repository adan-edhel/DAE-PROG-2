#include "pch.h"
#include "HUDManager.h"

#include <sstream>

#include "CORE.h"
#include "GameSettings.h"
#include <SpriteRenderer.h>

HUDManager::HUDManager()
{
}

void HUDManager::UpdatePlayerPosition(const Vector2& position)
{
	if (position != m_PlayerPosition)
	{
		m_PlayerPosition = position;
	}
}

void HUDManager::UpdatePlayerHealth(const int& health, const int& maxHealth)
{
	m_PlayerHealth = health;
	m_PlayerMaxHealth = maxHealth;
}

void HUDManager::Update(const float& deltaTime)
{
	for (int i = 0; i < m_AncientMasks.size(); i++)
	{
		m_AncientMasks[i].m_Active = false;
		if (i < m_PlayerHealth)
		{
			m_AncientMasks[i].m_Active = true;
		}
	}
}

void HUDManager::UIDraw() const
{
	// Draw player position
	if (!CORE::s_DebugMode) // TODO: Remove for release
	{
		DrawString(m_PlayerPosition.ToRoundedString(), Vector2(0, -350));
	}

	// Draw ancient masks (health)
	for (int i = 0; i < m_AncientMasks.size(); i++)
	{
		const float offsetPosX{m_MasksPositionsOrigin.x + (m_MasksOffset * float(i))};
		m_AncientMasks[i].Draw(Vector2(offsetPosX, m_MasksPositionsOrigin.y));
	}
}

void HUDManager::DrawString(const std::string& text, const Vector2 position) const
{
	const Texture m_PositionText{ text, m_Font, m_FontSize, m_FontColor };

	const float drawPosX{ GameSettings::s_ScreenSize.x / 2 - m_PositionText.GetWidth() / 2 };
	const float drawPosY{ GameSettings::s_ScreenSize.y / 2 - m_PositionText.GetHeight() / 2 };

	m_PositionText.Draw(Point2f(drawPosX + position.x ,drawPosY + position.y ));
}
