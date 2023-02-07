#include "Paddle.h"
#define _USE_MATH_DEFINES
#include <Math.h>

Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
}

void Paddle::draw(Graphics& gfx) const
{
	SpriteCodex::DrawPaddle(pos, gfx);
}

bool Paddle::ballCollision(Ball& ball) const
{
	if (getRect().isOverLapping(ball.getRect()))
	{
		Rect rect = getRect();
		Vec2 ballPrevPos = ball.prevPosition();
		Vec2 ballPos = Vec2(0, 0);

		float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballPrevPos.y - pos.y);
		float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballPrevPos.x - pos.x);
		float maxBounceAngle = 5 * M_PI / 12.0f;



		if (wy > hx)
		{
			if (wy > -hx)
			{
				//bottom
				ballPos.y += rect.bottom - ball.getRect().top;
				ball.reboundY(true);
			}
			else
			{
				//left
				ballPos.x -= ball.getRect().right - rect.left;
				ball.reboundX(false);
			}
		}
		else
		{
			if (wy > -hx)
			{
				//right
				ballPos.x += rect.right - ball.getRect().left;
				ball.reboundX(true);
			}
			else
			{
				//top
				ballPos.y -= ball.getRect().bottom - rect.top;
				const float relativeX = ballPrevPos.x - pos.x;
				const float bounceAngle = relativeX * (3 * float(M_PI) / 2) / (pos.x) + float(M_PI) / 2;
				ball.setDirection(Vec2( -cosf(bounceAngle) * BALL_SPEED, -sinf(bounceAngle) * BALL_SPEED) );
				
			}
		}
		ballPrevPos += ballPos;
		ball.setPosition(ballPrevPos);
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

Vec2 Paddle::getVec() const
{
	return pos;
}

void Paddle::setPos(const Vec2& pos_)
{
	pos = pos_;
}
