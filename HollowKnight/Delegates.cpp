#include "pch.h"
#include "Delegates.h"

Delegate<> Delegates::DrawObjects;
Delegate<const float&> Delegates::UpdateObjects;

Delegates::~Delegates()
{
}