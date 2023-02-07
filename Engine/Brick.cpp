#include "Brick.h"

Brick::Brick(const Rect& rect, Color c)
	:
	rect(rect),
	c(c)
{
	l = Colors::MakeRGB(230, 230, 230);
	d = Colors::MakeRGB(130, 130, 130);
}
	
void Brick::draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.getExpanded(-padding), c);

		gfx.DrawRect(Rect(rect.left + padding, rect.right - padding, (rect.bottom - padding) - width, (rect.bottom - padding)), d);
		gfx.DrawRect(Rect((rect.right - padding) - width, (rect.right - padding), rect.top + padding, rect.bottom - padding), d);

		gfx.DrawRect(Rect(rect.left + padding, rect.right - padding, rect.top + padding, (rect.top + padding) + width), l);
		gfx.DrawRect(Rect(rect.left + padding, (rect.left + padding) + width, rect.top + padding, rect.bottom - padding), l);


	}
}

bool Brick::isCollidingBall(const Ball& ball) const
{
	return !destroyed && rect.isOverLapping(ball.getRect());
}

void Brick::executeBallCollision(Ball& ball, const bool& type)
{
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
	if (type)
		destroyed = false;

	ballPrevPos += ballPos;
	ball.setPosition(ballPrevPos);
}

Rect Brick::getRect() const
{
	return rect;
}
