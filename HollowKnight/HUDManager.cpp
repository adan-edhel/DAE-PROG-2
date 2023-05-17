#include "pch.h"
#include "HUDManager.h"

#include <sstream>

#include "CORE.h"
#include "GameSettings.h"

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

void HUDManager::Update(const float& deltaTime)
{
}

void HUDManager::UIDraw() const
{
	if (!CORE::s_DebugMode) // TODO: Remove for release
	{
		DrawString(m_PlayerPosition.ToRoundedString(), Vector2(0, -350));
	}
}

void HUDManager::DrawString(const std::string& text, const Vector2 position) const
{
	const Texture m_PositionText{ text, m_Font, m_FontSize, m_FontColor };

	const float drawPosX{ GameSettings::s_ScreenSize.x / 2 - m_PositionText.GetWidth() / 2 };
	const float drawPosY{ GameSettings::s_ScreenSize.y / 2 - m_PositionText.GetHeight() / 2 };

	m_PositionText.Draw(Point2f(drawPosX + position.x ,drawPosY + position.y ));
}
