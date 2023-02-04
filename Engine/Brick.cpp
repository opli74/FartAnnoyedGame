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

	Vec2 ballPrevPos = ball.prevPosition();
	Vec2 ballPos = Vec2(0, 0);


	float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballPrevPos.y - rect.getCenter().y);
	float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballPrevPos.x - rect.getCenter().x);

	if (wy > hx)
	{
		if (wy > -hx)
		{
			//bottom
			ballPos.y += rect.bottom - ball.getRect().top;
			ball.reboundY(true);
			destroyed = true;
		}
		else
		{
			//left
			ballPos.x -= ball.getRect().right - rect.left;
			ball.reboundX(false);
			destroyed = true;
		}
	}
	else
	{
		if (wy > -hx)
		{
			//right
			ballPos.x += rect.right - ball.getRect().left;
			ball.reboundX(true);
			destroyed = true;
		}
		else
		{
			//top
			ballPos.y -= ball.getRect().bottom - rect.top;
			ball.reboundY(false);
			destroyed = true;
		}
	}
	ball.setPosition(ballPos);
}

Rect Brick::getRect() const
{
	return rect;
}
