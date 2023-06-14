#include "pch.h"
#include "Menu.h"

#include "AudioLibrary.h"
#include "CORE.h"
#include "GameSettings.h"
#include "SceneManager.h"
#include "SpriteLibrary.h"
#include <AudioSource.h>
#include "utils.h"

Menu::Menu()
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

	if (m_MusicSource == nullptr)
	{
		m_MusicSource = m_AudioSource.AddComponent(new AudioSource(true, false, true));
	}

	m_MusicSource->SetClip(AudioLibrary::GetClip(Music::Title));
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
			m_MusicSource->Stop();
			SceneManager::LoadScene(Scene::Game);
			break;
		case Buttons::Controls:
			m_ActivePage = Page::Controls;
			break;
		case Buttons::Quit:
			SDL_Event quit{};
			quit.type = SDL_QUIT;
			SDL_PushEvent(&quit);
			Print("###################################\n");
			Print("#     THANK YOU FOR PLAYING!      #\n");
			Print("###################################\n");
			Print("#          HOLLOW KNIGHT          #\n");
			Print("###################################\n");
			Print("#        (Re)Made by Mort         #\n");
			Print("###################################\n");
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

	if (m_ActiveButton != Buttons::None)
	{
		AudioLibrary::PlayClip(Audio::ButtonConfirm);
	}
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
				AudioLibrary::PlayClip(Audio::ButtonHighlight);

				if (CORE::s_DebugMode)
				{
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
				}
			}
			m_ActiveButton = button;
			m_LastSelectedButton = m_ActiveButton;
			return;
		}
		m_ActiveButton = Buttons::None;
	}
}