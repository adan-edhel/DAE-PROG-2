#pragma once
#include "IDrawable.h"
#include "SpriteLibrary.h"

#include "Knight.h"

class HUDManager : public IUpdatable, public IDrawable
{
public:
	HUDManager();

	static void UpdatePlayerPosition(const Vector2& position);

private:
	// Text settings
	int m_FontSize{ 30 };
	Color4f m_FontColor{ 0.5f, 0.5f, 0.5f, 1 };
	std::string m_Font{ SpriteLibrary::GetFont(Font::TrajanPro) };

	//Debug values
	inline static Vector2 m_PlayerPosition{};

	//std::vector<GameObject> HealthIcons{};

	void Update(const float& deltaTime) override;
	void UIDraw() const override;

	void DrawString(const std::string& text, const Vector2 position = Vector2{}) const;
};

