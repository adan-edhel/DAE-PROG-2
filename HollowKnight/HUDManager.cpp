#include "pch.h"
#include "HUDManager.h"

HUDManager::HUDManager() : IDrawable(int(Layers::UserInterface))
{
}

void HUDManager::UIDraw() const
{
	m_PositionText.Draw();
}