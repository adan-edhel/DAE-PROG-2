#pragma once
#include <vector>
#include "IDrawable.h"
#include "SpriteLibrary.h"

#include "Knight.h"

class HUDManager : public IDrawable
{
public:
	HUDManager();

	std::string position{Knight::s_Position.ToString()};
	Texture m_PositionText{position, SpriteLibrary::GetFont(Font::TrajanPro), 34, Color4f(0.5f, .5f, 0.5f, 1)};

private:
	//std::vector<GameObject> HealthIcons{};

	void UIDraw() const override;
};

