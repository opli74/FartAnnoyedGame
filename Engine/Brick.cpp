#include "Brick.h"

Brick::Brick(const Rect& rect, Color c, const int health)
	:
	rect(rect),
	c(c),
	health(health)
{
}
	
void Brick::draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		if (hit)
			gfx.DrawRect(rect.getExpanded(-padding), Colors::White);
		else
			gfx.DrawRect(rect.getExpanded(-padding), c);

		gfx.DrawRect(Rect(rect.left + padding, rect.right - padding, (rect.bottom - padding) - width, (rect.bottom - padding)), d);
		gfx.DrawRect(Rect((rect.right - padding) - width, (rect.right - padding), rect.top + padding, rect.bottom - padding), d);

		gfx.DrawRect(Rect(rect.left + padding, rect.right - padding, rect.top + padding, (rect.top + padding) + width), l);
		gfx.DrawRect(Rect(rect.left + padding, (rect.left + padding) + width, rect.top + padding, rect.bottom - padding), l);


	}
}

bool Brick::isCollidingBall(const Ball& ball)
{
	if (!destroyed && rect.isOverLapping(ball.getRect()))
	{
		return true;
		
	}
	return false;
	
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
			health -= 1;
		}
		else
		{
			//left
			ballPos.x -= ball.getRect().right - rect.left;
			ball.reboundX(false);
			health -= 1;
		}
	}
	else
	{
		if (wy > -hx)
		{
			//right
			ballPos.x += rect.right - ball.getRect().left;
			ball.reboundX(true);
			health -= 1;
		}
		else
		{
			//top
			ballPos.y -= ball.getRect().bottom - rect.top;
			ball.reboundY(false);
			health -= 1;
		}
	}
	
	if (health > 0 || type)
		destroyed = false;
	else
		destroyed = true;

	ballPrevPos += ballPos;
	ball.setPosition(ballPrevPos);
}

Color Brick::getColor() const
{
	return c;
}

void Brick::setColor(const Color& in)
{
	c = in;
}

Rect Brick::getRect() const
{
	return rect;
}

void Brick::color()
{
	if (hit)
	{
		frames++;
		if (frames > 25)
		{
			frames = 0;
			hit = false;
		}
			
	}
}
