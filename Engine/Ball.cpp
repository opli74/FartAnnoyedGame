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

	prevPos = pos - (vel * dt);
}

int Ball::wallCollision(const Rect& wall)
{
	int collided = 0;
	const Rect rect = getRect();
	if (rect.left < wall.left)
	{
		pos.x += wall.left - rect.left;
		reboundX();
		collided = 1;
	}
	else if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		reboundX();
		collided = 1;
	}
	if (rect.top < wall.top)
	{
		pos.y += wall.top - rect.top;
		reboundY();
		collided = 1;
	}
	else if (rect.bottom > wall.bottom)
	{
		restart = true;
	}
	return collided;
}

void Ball::reboundX()
{
	vel.x = -vel.x;
}

void Ball::reboundX(const bool& dir)
{
	if (dir)
		vel.x = abs(vel.x);
	else
		vel.x = -abs(vel.x);
}

void Ball::reboundY(const bool& dir)
{
	if (dir)
		vel.y = abs(vel.y);
	else
		vel.y = -abs(vel.y);
}

Vec2 Ball::prevPosition() const
{
	return prevPos;
}

void Ball::reboundY() 
{
	vel.y = -vel.y;
}

Vec2 Ball::getPosition() const
{
	return pos;
}

Vec2 Ball::getVelocity() const
{
	return vel;
}

bool Ball::getRestart() const
{
	return restart;
}

Rect Ball::getRect() const
{
	return Rect::fromCenter(pos, radius, radius);
}

void Ball::setDirection(const Vec2& vel_)
{
	vel = vel_;
}

void Ball::setPosition(const Vec2& pos_)
{
	pos = pos_;
}

void Ball::switchRestart()
{
	restart = !restart;
}


