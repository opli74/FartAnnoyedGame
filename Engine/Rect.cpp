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
	return left > rect.right && right < rect.left&& bottom > rect.top && top < rect.bottom;
}
