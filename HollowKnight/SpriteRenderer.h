#pragma once
#include "IComponent.h"
#include "Texture.h"
#include "Vector2.h"

class Transform;

class SpriteRenderer : public IComponent
{
private:
	Texture* m_Sprite{};

public:

	Vector2 Bounds() const;

	SpriteRenderer();
	void Draw() const;
	void Update(const float& deltaTime) override;
	~SpriteRenderer();
};

