#include "Transform.h"

#include "AmrothUtils.h"

Transform::Transform()
{
}

void Transform::Translate(const float& x, const float& y) { Translate(Vector2(x, y)); }
void Transform::Translate(const Vector2& displacement)
{
	position += displacement;
}

void Transform::DebugDraw() const
{
	glColor3f(1, 0, 0);
	DrawCircle(position.x, position.y, 3, 90);
}