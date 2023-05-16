#include "pch.h"
#include "HUDManager.h"

#include <sstream>

#include "GameSettings.h"

HUDManager::HUDManager()
{
}

void HUDManager::UpdatePlayerPosition(const Vector2& position)
{
	m_PlayerPosition = position;
}

void HUDManager::Update(const float& deltaTime)
{
}

void HUDManager::UIDraw() const
{
	DrawString(m_PlayerPosition.ToRoundedString(), Vector2(0, -350));
}

void HUDManager::DrawString(const std::string& text, const Vector2 position) const
{
	return;
	const Texture m_PositionText{text, m_Font, m_FontSize, m_FontColor };

	const float drawPosX{ GameSettings::s_Screen.x / 2 - m_PositionText.GetWidth() / 2 };
	const float drawPosY{ GameSettings::s_Screen.y / 2 - m_PositionText.GetHeight() / 2 };

	m_PositionText.Draw(Point2f(drawPosX + position.x ,drawPosY + position.y ));
}
