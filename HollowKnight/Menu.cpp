#include "pch.h"
#include "Menu.h"

#include "GameSettings.h"
#include "SpriteLibrary.h"

Menu::Menu()
{
	m_BackgroundPtr = SpriteLibrary::GetSprite(Sprite::MenuBackground);
	m_TitlePtr = SpriteLibrary::GetSprite(Sprite::MenuTitle);

	const float backgroundMult = 1.4f;
	const float titleMult = 0.6f;
	const float titleOffset = 175;

	m_BackgroundRect.width = m_BackgroundPtr->GetWidth() * backgroundMult;
	m_BackgroundRect.height = m_BackgroundPtr->GetHeight() * backgroundMult;
	m_BackgroundRect.left = GameSettings::s_ScreenCenter.x - m_BackgroundRect.width / 2;
	m_BackgroundRect.bottom = GameSettings::s_ScreenCenter.y - m_BackgroundRect.height / 2;

	m_TitleRect.width = m_TitlePtr->GetWidth() * titleMult;
	m_TitleRect.height = m_TitlePtr->GetHeight() * titleMult;
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