#include "pch.h"
#include "Menu.h"

#include "GameSettings.h"
#include "SpriteLibrary.h"

Menu::Menu()
{
	m_BackgroundPtr = SpriteLibrary::GetSprite(Sprite::MenuBackground);
	m_TitlePtr = SpriteLibrary::GetSprite(Sprite::MenuTitle);

	const float backgroundMultiplier = 1.4f;
	const float titleMultiplier = 0.6f;
	const float titleOffset = 175;

	m_BackgroundRect.width = m_BackgroundPtr->GetWidth() * backgroundMultiplier;
	m_BackgroundRect.height = m_BackgroundPtr->GetHeight() * backgroundMultiplier;
	m_BackgroundRect.left = GameSettings::s_ScreenCenter.x - m_BackgroundRect.width / 2;
	m_BackgroundRect.bottom = GameSettings::s_ScreenCenter.y - m_BackgroundRect.height / 2;

	m_TitleRect.width = m_TitlePtr->GetWidth() * titleMultiplier;
	m_TitleRect.height = m_TitlePtr->GetHeight() * titleMultiplier;
	m_TitleRect.left = GameSettings::s_ScreenCenter.x - m_TitleRect.width / 2;
	m_TitleRect.bottom = GameSettings::s_ScreenCenter.y - m_TitleRect.height / 2 + titleOffset;
}

void Menu::Update(const float& deltaTime)
{
}

void Menu::Draw() const
{
	m_BackgroundPtr->Draw(m_BackgroundRect);
	m_TitlePtr->Draw(m_TitleRect);

	for (int i = 0; i < m_Buttons.size(); i++)
	{
		DrawButton(m_Buttons[i], float(i) * m_ButtonsOffset);
	}
}

void Menu::DrawButton(const Texture& texture, const float& offset) const
{
	const float positionX = GameSettings::s_ScreenCenter.x - texture.GetWidth() / 2;
	const float positionY = GameSettings::s_ScreenCenter.y - texture.GetHeight() / 2 - offset;

	texture.Draw(Point2f(positionX,positionY + m_ButtonsPosOffset));
}