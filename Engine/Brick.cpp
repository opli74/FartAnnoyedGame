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

bool Brick::isCollidingBall(const Ball& ball) const
{
	return !destroyed && rect.isOverLapping(ball.getRect());
}

void Brick::executeBallCollision(Ball& ball)
{

	//float left = ball.getRect().right - rect.left;
	//float right = rect.right - ball.getRect().left;
	//float top = ball.getRect().bottom - rect.top;
	//float bottom = rect.bottom - ball.getRect().top;

	Vec2 ballPos = ball.prevPosition();

	float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballPos.y - rect.getCenter().y);
	float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballPos.x - rect.getCenter().x);

	if (wy > hx)
	{
		if (wy > -hx)
		{
			//bottom
			ball.pos.y += rect.bottom - ball.getRect().top;
			ball.reboundY(true);
			destroyed = true;
		}
		else
		{
			//left
			ball.pos.x -= ball.getRect().right - rect.left;
			ball.reboundX(false);
			destroyed = true;
		}
	}
	else
	{
		if (wy > -hx)
		{
			//right
			ball.pos.x += rect.right - ball.getRect().left;
			ball.reboundX(true);
			destroyed = true;
		}
		else
		{
			//top
			ball.pos.y -= ball.getRect().bottom - rect.top;
			ball.reboundY(false);
			destroyed = true;
		}
	}
	
}

Rect Brick::getRect() const
{
	return rect;
}
