#pragma once
#include "Vector2.h"

class InputActions
{
protected:
	Vector2 m_MousePos{};

	virtual void Walk() = 0;
	virtual void Jump() = 0;
	virtual void CutJump() = 0;
	virtual void Attack() = 0;

	virtual ~InputActions() = default;
};

