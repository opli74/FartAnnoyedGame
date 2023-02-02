#include "Brick.h"

Brick::Brick(const Rect& rect, Color c)
	:
	rect(rect),
	c(c)
{
}
	
void Brick::draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect, c);
	}
}

bool Brick::isCollidingBall(Ball& ball)
{
	if (!destroyed && rect.isOverLapping(ball.getRect()))
	{
		ball.reboundY();
		destroyed = true;
		return true;
	}
	return false;
}

void Brick::executeBallCollision(Ball& ball)
{
}
