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
	if (ball.getVelocity().y > 0.0f && getRect().isOverLapping(ball.getRect()))
	{
		ball.reboundY();
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
