#include "Paddle.h"

Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
}

void Paddle::draw(Graphics& gfx) const
{
	gfx.DrawRect(getRect(), c);
}

bool Paddle::ballCollision(Ball& ball) const
{
	if (getRect().isOverLapping(ball.getRect()))
	{
		Rect rect = getRect();
		Vec2 ballPos = ball.prevPosition();

		float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballPos.y - pos.y);
		float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballPos.x - pos.x);

		if (wy > hx)
		{
			if (wy < -hx)
			{
				//left
				ball.pos.x -= ball.getRect().right - rect.left;
				ball.reboundX(false);

			}
			else
			{
				//bottom
				ball.pos.y += rect.bottom - ball.getRect().top;
				ball.reboundY(true);
			}
		}
		else
		{
			if (wy > -hx)
			{
				//right
				ball.pos.x += rect.right - ball.getRect().left;
				ball.reboundX(true);
			}
			else
			{
				//top
				ball.pos.y -= ball.getRect().bottom - rect.top;
				ball.reboundY(false);
			}
		}
		return true;
	}
	return false;
}

void Paddle::wallCollision(const Rect& wall)
{
	const Rect rect = getRect();
	if (rect.left <= wall.left)
	{
		pos.x += wall.left - rect.left ;
	}
	if (rect.right >= wall.right)
	{
		pos.x -= rect.right - wall.right;
	}
}

void Paddle::update(const Keyboard& kbd, float dt)
{
	
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

Rect Paddle::getRect() const
{
	return Rect::fromCenter(pos, halfWidth, halfHeight);
}
