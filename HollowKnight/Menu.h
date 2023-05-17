#pragma once
#include <array>
#include "SpriteLibrary.h"

enum class Buttons
{
	Start,
	Controls,
	Quit
};

class Menu final
{
public:
	Menu();
	void Update(const float& deltaTime);
	void Draw() const;
	void DrawButton(const Texture& texture, const float& offset) const;

private:
	// Background Pointers
	Texture* m_BackgroundPtr{};
	Texture* m_TitlePtr{};

	// Background Rects
	Rectf m_BackgroundRect{};
	Rectf m_TitleRect{};

	// Active Button
	Buttons m_ActiveButton{};

	// Text settings
	int m_FontSize{ 20 };
	Color4f m_FontColor{ 1.0f, 1.0f, 1.0f, 1 };
	std::string m_Font{ SpriteLibrary::GetFont(Font::TrajanPro) };

	const float m_ButtonsOffset{75};
	const float m_ButtonsPosOffset{-50};

	// Buttons
	std::array<Texture, 3> m_Buttons = {
		Texture("Start Game", m_Font, m_FontSize, m_FontColor),
		Texture("Controls", m_Font, m_FontSize, m_FontColor),
		Texture("Quit Game", m_Font, m_FontSize, m_FontColor) };

	std::array<Rectf, 3> m_ButtonBounds = {};
};
