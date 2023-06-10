#include "pch.h"
#include "Menu.h"

#include "GameSettings.h"
#include "SceneManager.h"
#include "SpriteLibrary.h"
#include "utils.h"

Menu::Menu() :
	m_MenuMusic{ "HollowKnight/Audio/Music/TitleTheme.wav" },
	m_HighlightSound{"HollowKnight/Audio/UI/ui_change_selection.wav"},
	m_ConfirmSound{"HollowKnight/Audio/UI/ui_button_confirm.wav"}
{
	m_BackgroundPtr = SpriteLibrary::GetSprite(Sprite::MenuBackground);
	m_TitlePtr = SpriteLibrary::GetSprite(Sprite::MenuTitle);

	const float backgroundMultiplier = 1.4f;
	const float titleMultiplier = 0.6f;
	const float titleOffset = 175;

	// Background Positioning
	m_BackgroundRect.width = m_BackgroundPtr->GetWidth() * backgroundMultiplier;
	m_BackgroundRect.height = m_BackgroundPtr->GetHeight() * backgroundMultiplier;
	m_BackgroundRect.left = GameSettings::s_ScreenCenter.x - m_BackgroundRect.width / 2;
	m_BackgroundRect.bottom = GameSettings::s_ScreenCenter.y - m_BackgroundRect.height / 2;

	// Title Positioning
	m_TitleRect.width = m_TitlePtr->GetWidth() * titleMultiplier;
	m_TitleRect.height = m_TitlePtr->GetHeight() * titleMultiplier;
	m_TitleRect.left = GameSettings::s_ScreenCenter.x - m_TitleRect.width / 2;
	m_TitleRect.bottom = GameSettings::s_ScreenCenter.y - m_TitleRect.height / 2 + titleOffset;

	// Buttons Positioning
	for (int i = 0; i < m_Buttons.size(); i++)
	{
		const float centerXPos{ GameSettings::s_ScreenCenter.x - m_Buttons[i].GetWidth() / 2 };
		const float centerYPos{ GameSettings::s_ScreenCenter.y - m_Buttons[i].GetHeight() / 2 };

		m_ButtonBounds[i].width = m_Buttons[i].GetWidth();
		m_ButtonBounds[i].height = m_Buttons[i].GetHeight();
		m_ButtonBounds[i].left = centerXPos;
		m_ButtonBounds[i].bottom = centerYPos - (i * m_ButtonsOffset);
	}

	m_MenuMusic.Play(-1);
}

void Menu::Draw() const
{
	// Draw Background & Title
	m_BackgroundPtr->Draw(m_BackgroundRect);
	m_TitlePtr->Draw(m_TitleRect);

	switch (m_ActivePage)
	{
	case Page::Menu:
		// Draw Buttons
		for (int i = 0; i < m_Buttons.size() - 1; i++)
		{
			m_Buttons[i].Draw(m_ButtonBounds[i]);
		}
		break;
	case Page::Controls:
		m_Buttons[m_Buttons.size() - 1].Draw(m_ButtonBounds[m_Buttons.size() - 1]);
		break;
	}
}

void Menu::SelectButton()
{
	switch (m_ActivePage)
	{
	case Page::Menu:
		switch (m_ActiveButton)
		{
		case Buttons::Start:
			SceneManager::SetScene(Scene::Game);
			break;
		case Buttons::Controls:
			m_ActivePage = Page::Controls;
			break;
		case Buttons::Quit:
			Print("Quit Game! [Implement for release...]\n");
			break;
		}
		break;
	case Page::Controls:
		switch (m_ActiveButton)
		{
		case Buttons::Back:
			m_ActivePage = Page::Menu;
			break;
		}
		break;
	}
	m_ConfirmSound.Play();
}

void Menu::HighlightButton(const float& mouseX, const float& mouseY)
{
	for (int i = 0; i < m_ButtonBounds.size(); i++)
	{
		if (utils::IsPointInRect(Point2f(mouseX, mouseY), m_ButtonBounds[i]))
		{
			const Buttons button{ Buttons(i + 1) };

			if (m_LastSelectedButton != button)
			{
				//TODO: Play UI sound
				switch (button)
				{
					case Buttons::Start:
						Print("Start Highlighted!\n");
						break;
					case Buttons::Controls:
						Print("Controls Highlighted!\n");
						break;
					case Buttons::Quit:
						Print("Quit Highlighted!\n");
						break;
					case Buttons::Back:
						Print("Back Highlighted!\n");
						break;
				}
				m_HighlightSound.Play();
			}
			m_ActiveButton = button;
			m_LastSelectedButton = m_ActiveButton;
			return;
		}
		m_ActiveButton = Buttons::None;
	}
}