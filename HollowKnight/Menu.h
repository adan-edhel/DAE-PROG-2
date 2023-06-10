#pragma once
#include <array>

#include "GameObject.h"
#include "SoundEffect.h"
#include "SpriteLibrary.h"

class Menu final
{
	enum class Page
	{
		Menu,
		Controls
	};

	enum class Buttons
	{
		None,
		Start,
		Controls,
		Quit,
		Back
	};

public:
	Menu();
	void Draw() const;
	void SelectButton();
	void HighlightButton(const float& mouseX, const float& mouseY);

private:
	SoundEffect m_MenuMusic;
	SoundEffect m_HighlightSound;
	SoundEffect m_ConfirmSound;

	// Background Pointers
	Texture* m_BackgroundPtr{};
	Texture* m_TitlePtr{};

	// Background Rects
	Rectf m_BackgroundRect{};
	Rectf m_TitleRect{};

	// Active Button
	Page m_ActivePage{};
	Buttons m_ActiveButton{};
	Buttons m_LastSelectedButton{};

	// Text settings
	int m_FontSize{ 20 };
	Color4f m_FontColor{ 1.0f, 1.0f, 1.0f, 1 };
	std::string m_Font{ SpriteLibrary::GetFont(Font::TrajanPro) };

	const float m_ButtonsOffset{75};
	const float m_ButtonsPosOffset{-50};

	// Buttons
	std::array<Texture, 4> m_Buttons = {
		Texture("Start Game", m_Font, m_FontSize, m_FontColor),
		Texture("Controls", m_Font, m_FontSize, m_FontColor),
		Texture("Quit Game", m_Font, m_FontSize, m_FontColor),
		Texture("Back", m_Font, m_FontSize, m_FontColor)};

	std::array<Rectf, 4> m_ButtonBounds = {};

	// Button Details
	GameObject m_ButtonAccents{};
};
