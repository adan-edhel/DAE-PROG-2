#pragma once
class Transform;

class IComponent
{
public:
	Transform* m_Transform;
	virtual void Update(const float& deltaTime) = 0;
};