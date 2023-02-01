#include "Ball.h"
#include "SpriteCodex.h"
#include <assert.h>

Ball::Ball(const Vec2& pos, const Vec2& vel)
	:
	vel(vel),
	pos(pos)
{
}

void Ball::draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::update(float dt)
{
	pos += vel * dt;
}

bool Ball::wallCollision(const Rect& wall)
{
	bool collided = false;
	const Rect rect = getRect();
	if (rect.left <= wall.left)
	{
		pos.x += wall.left - rect.left;
		reboundX();
		collided = true;
	}
	else if (rect.right >= wall.right)
	{
		pos.x -= rect.right - wall.right;
		reboundX();
		collided = true;
	}
	if (rect.top <= wall.top)
	{
		pos.y += wall.top - rect.top;
		reboundY();
		collided = true;
	}
	else if (rect.bottom >= wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		reboundY();
		collided = true;
	}
	return collided;
}

void Ball::reboundX()
{
	vel.x = -vel.x;
}

void Ball::reboundY()
{
	vel.y = -vel.y;
}

Rect Ball::getRect() const
{
	return Rect::fromCenter(pos, radius, radius);
}


