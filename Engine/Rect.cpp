#include "Rect.h"

Rect::Rect(float left, float right, float top, float bottom)
	:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
}

Rect::Rect(const Vec2& topLeft, const Vec2& bottomRight)
	:
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rect::Rect(const Vec2& topLeft, float width, float height)
	:
	Rect(topLeft, topLeft + Vec2(width, height))
{
}

bool Rect::isOverLapping(const Rect& rect) const
{
	return right > rect.left && left < rect.right
		&& bottom > rect.top && top < rect.bottom;
}

Rect Rect::fromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return Rect(center - half, center + half);
}

Rect Rect::getExpanded(float offset) const
{
	return Rect(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 Rect::getCenter() const
{
	return Vec2((left + right) / 2.0f, (bottom + top) / 2);
}
