#pragma once
#include <array>

#include "GameObject.h"
#include "IInputEvent.h"
#include "SpriteLibrary.h"

class AudioSource;

class Menu final : IInputEvent
{
	struct Pointer
	{
		void Draw(const Rectf& button) const
		{
			const Texture* sprite{ SpriteLibrary::GetSprite(Sprite::Pointer) };

			const float scale{ 0.5f };

			Rectf drawRect{};
			drawRect.width = sprite->GetWidth() * scale;
			drawRect.height = sprite->GetHeight() * scale;

			// Draw left
			glPushMatrix();
			glTranslatef(button.left - drawRect.width, button.bottom, 0);
			sprite->Draw(drawRect);
			glPopMatrix();

			// Draw right
			glPushMatrix();
			glTranslatef(button.left + button.width + drawRect.width, button.bottom, 0);
			glScalef(-1, 1, 1);
			sprite->Draw(drawRect);
			glPopMatrix();
		}
	};

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
		Back,
		Buttons_Count
	};

public:
	Menu();
	void Draw() const;

private:
	// Audio
	GameObject m_AudioSource{};
	AudioSource* m_MusicSource{};

	// Background Pointers
	Texture* m_BackgroundPtr{};
	Texture* m_TitlePtr{};

	// Background Rects
	Rectf m_BackgroundRect{};
	Rectf m_TitleRect{};

	// Active Checks
	Page m_ActivePage{};
	Buttons m_ActiveButton{};
	Buttons m_LastSelectedButton{};

	// Text settings
	int m_FontSize{ 26 };
	Color4f m_FontColor{ 1.0f, 1.0f, 1.0f, 1 };
	std::string m_Font{ SpriteLibrary::GetFont(Font::TrajanPro) };

	static const int m_MenuButtonCount{ 3 };
	static const int m_ControlsButtonCount{ 1 };

	const float m_ButtonsOffset{ 56 };
	const float m_ButtonsPosOffset{ -50 };

	// Buttons
	std::array<Texture, m_MenuButtonCount + m_ControlsButtonCount> m_Buttons{
		Texture("Start Game", m_Font, m_FontSize, m_FontColor),
		Texture("Options", m_Font, m_FontSize, m_FontColor),
		Texture("Quit Game", m_Font, m_FontSize, m_FontColor),
		Texture("Back", m_Font, m_FontSize, m_FontColor) };

	// Button Bounds
	std::array<Rectf, m_MenuButtonCount + m_ControlsButtonCount> m_ButtonBounds{};

	// Button Pointers
	Pointer m_ButtonPointers{};

	// Button Details
	GameObject m_ButtonAccents{};

	void SelectButton();
	void HighlightButton(const float& mouseX, const float& mouseY);
	void VisualizeHighlights() const;
	void MoveSelectedButton(int&& x, int&& y);

	void OnMouseMotion(const SDL_MouseMotionEvent& e) override;
	void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	void OnKeyDown(const SDL_KeyboardEvent& e) override;
};
