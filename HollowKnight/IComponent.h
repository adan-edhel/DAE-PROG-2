#pragma once

class Transform;

class IComponent
{
public:
	bool* m_pIsActive;
	Transform* m_pTransform;
	virtual ~IComponent() = default;
};