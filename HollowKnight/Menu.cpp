#include "pch.h"
#include "Menu.h"

#include "AudioLibrary.h"
#include "SpriteLibrary.h"

#include "GameSettings.h"
#include "SceneManager.h"

#include <AudioSource.h>
#include <SoundEffect.h>
#include "utils.h"
#include <CORE.h>


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

	m_MusicSource->AssignClip(AudioLibrary::GetClip(Music::Title));
}

void Menu::Draw() const
{
	// Draw Background & Title
	m_BackgroundPtr->Draw(m_BackgroundRect);
	m_TitlePtr->Draw(m_TitleRect);

	// Draw Buttons
	switch (m_ActivePage)
	{
	case Page::Menu:
		for (int i = 0; i < m_MenuButtonCount; i++)
		{
			m_Buttons[i].Draw(m_ButtonBounds[i]);
		}
		break;
	case Page::Controls:
		for (int i = m_MenuButtonCount; i < m_MenuButtonCount + m_OptionsButtonCount; i++)
		{
			m_Buttons[i].Draw(m_ButtonBounds[i]);
		}
		break;
	}

	VisualizeHighlights();

	if (CORE::s_DebugMode)
	{
		for (int i = 0; i < m_ButtonBounds.size(); i++)
		{
			utils::DrawRect(m_ButtonBounds[i]);
		}
	}
}

void Menu::SelectButton()
{
	switch (m_ActiveButton)
	{
	case Buttons::Start:		// START
		SceneManager::LoadScene(Scene::Game);
		AudioLibrary::PlayClip(Audio::ButtonConfirm);
		return;
	case Buttons::Controls:		// CONTROLS
		m_ActivePage = Page::Controls;
		m_ActiveButton = Buttons::Back;
		break;
	case Buttons::SoundOn:		// Sound On
		SoundEffect::SetGlobalVolume(1);
		break;
	case Buttons::SoundOff:		// Sound off
		SoundEffect::SetGlobalVolume(0);
		break;
	case Buttons::Back:			// BACK
		m_ActivePage = Page::Menu;
		break;
	case Buttons::Quit:			// QUIT (needs to be placed last)
		SceneManager::Quit();
		break;
	}

	if (m_ActiveButton != Buttons::None)
	{
		AudioLibrary::PlayClip(Audio::ButtonConfirm);
		m_ActiveButton = Buttons::None;
	}
}

void Menu::HighlightButton(const float& mouseX, const float& mouseY)
{
	for (int i = 0; i < m_ButtonBounds.size(); i++)
	{
		// Deactivate buttons depending on active page
		switch (m_ActivePage)
		{
		case Page::Menu:
			if (i > m_MenuButtonCount - 1) continue;
			break;
		case Page::Controls:
			if (i < m_MenuButtonCount) continue;
			break;
		}

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
					case Buttons::SoundOn:
						Print("Volume Up Highlighted!\n");
						break;
					case Buttons::SoundOff:
						Print("Volume Down Highlighted!\n");
						break;
					case Buttons::Back:
						Print("Back Highlighted!\n");
						break;
					case Buttons::Quit:
						Print("Quit Highlighted!\n");
						break;
					}
				}
				m_ActiveButton = button;
				m_LastSelectedButton = m_ActiveButton;
			}
			return;
		}
	}
}

void Menu::MoveSelectedButton(int&& x, int&& y)
{
	int nextButton{ int(m_ActiveButton) };

	if (y > 0) nextButton--;
	else if (y < 0) nextButton++;

	switch (m_ActivePage)
	{
	case Page::Menu:
		if (nextButton <= 0 || nextButton > int(Buttons::Quit)) return;
		break;
	case Page::Controls:
		if (nextButton <= m_MenuButtonCount || nextButton >= int(Buttons::Buttons_Count)) return;
		break;
	}

	m_ActiveButton = Buttons(nextButton);
	AudioLibrary::PlayClip(Audio::ButtonConfirm);
}

void Menu::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	SceneManager::GetScene<Menu>()->HighlightButton(e.x, e.y);
}

void Menu::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	SelectButton();
}

void Menu::OnKeyDown(const SDL_KeyboardEvent& e)
{
	int nextButton{};

	switch (e.keysym.sym)
	{
	case SDLK_RETURN:
		SceneManager::GetScene<Menu>()->SelectButton();
		break;
	case SDLK_UP:
		MoveSelectedButton(0, 1);
		break;
	case SDLK_DOWN:
		MoveSelectedButton(0, -1);
		break;
	}
}

void Menu::VisualizeHighlights() const
{
	if (m_ActiveButton == Buttons::None) return;

	for (int i = 0; i <= m_ButtonBounds.size() - 1; i++)
	{
		if (static_cast<int>(m_ActiveButton) == i + 1)
		{
			m_ButtonPointers.Draw(m_ButtonBounds[i]);
		}
	}
}
