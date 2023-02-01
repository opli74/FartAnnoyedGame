#include "Brick.h"

Brick::Brick(const Rect& rect, Color c)
	:
	rect(rect),
	c(c)
{
}

void Brick::draw(Graphics& gfx) const
{
	gfx.DrawRect(rect, c);
}
