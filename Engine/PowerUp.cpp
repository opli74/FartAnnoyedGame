#include "PowerUp.h"


PowerUp::PowerUp(Rect& rect)
	:
	pos(rect.getCenter())
{
}

void PowerUp::draw(Graphics& gfx) const
{
	if (!destroyed)
		gfx.DrawRect(Rect::fromCenter(pos, width, height), Colors::MakeRGB(10, 10, 10));
}

Rect PowerUp::getRect() const
{
	return Rect::fromCenter(pos, width / 2.0f, height / 2.0f);
}

void PowerUp::update(float dt)
{
	if (!destroyed)
		pos += vel * dt;
}

bool PowerUp::paddleCollision(Paddle& paddle)
{
	if (getRect().isOverLapping(paddle.getRect()))
	{
		destroyed = true;
		return true;
	}
	return false;
}

void PowerUp::wallCollision(const Rect& wall)
{
	const Rect rect = getRect();
	if (rect.bottom >= wall.bottom)
	{
		destroyed = true;
	}
}
