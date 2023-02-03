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
		gfx.DrawRect(rect.getExpanded(-padding), c);
	}
}

bool Brick::isCollidingBall(Ball& ball)
{
	if (!destroyed && rect.isOverLapping(ball.getRect()))
	{
		float left = ball.getRect().right - rect.left;
		float right = rect.right - ball.getRect().left;
		float top = ball.getRect().bottom - rect.top;
		float bottom = rect.bottom - ball.getRect().top;

		//left
		if (left < right && left < top && left < bottom)
		{
			ball.pos.x -= left;
			ball.reboundX();
			destroyed = true;
			return true;
		}
			
		//right
		if (right < left && right < top && right < bottom) 
		{
			ball.pos.x += right;
			ball.reboundX();
			destroyed = true;
			return true;
		}

		//top
		if (top < right && top < left && top < bottom)
		{
			ball.pos.y -= top;
			ball.reboundY();
			destroyed = true;
			return true;
		}

		//bottom
		if (bottom < right && bottom < left && bottom < top)
		{
			ball.pos.y += bottom;
			ball.reboundY();
			destroyed = true;
			return true;
		}
	}

	//if (!destroyed && (rect.left > ball.getRect().right && rect.right < ball.getRect().left))
	//{
	//	ball.reboundX();
	//	destroyed = true;
	//	return
	//}
	return false;
}

void Brick::executeBallCollision(Ball& ball)
{
}
