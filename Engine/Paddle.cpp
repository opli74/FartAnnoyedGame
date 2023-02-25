#include "Paddle.h"
#define _USE_MATH_DEFINES
#include <Math.h>



Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
	diff = ( ( longHalfWidth - halfWidth ) / 2 ) * 2;
}

void Paddle::draw(Graphics& gfx)
{
	if ( !incLength )
	{
		SpriteCodex::DrawPaddle( pos , gfx , 0 );
	}
	else
	{
		if ( amount <= int(diff) )
		{
			if ( frames >= 0.03f )
			{
				amount++;
				frames = 0;
			}
		}
		SpriteCodex::DrawPaddle( pos , gfx , amount );
	}
}

bool Paddle::ballCollision(Ball& ball)
{
	if (getRect().isOverLapping(ball.getRect()))
	{
		Rect rect = getRect();
		Vec2 ballCurrPos = ball.getPosition();
		Vec2 ballPos = Vec2(0, 0);

		float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballCurrPos.y - pos.y);
		float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballCurrPos.x - pos.x);

		if (wy > hx)
		{
			if (wy < -hx)
			{
				//left
				ballPos.x -= ball.getRect().right - rect.left;
				ball.reboundX(false);
				if (ball.getVelocity().y > 0.0f)
					ballPos.y += rect.bottom - ball.getRect().top;
				else
					ballPos.y -= ball.getRect().bottom - rect.top;
				test = true;
			}
		}
		else
		{
			if (wy > -hx)
			{
				//right
				ballPos.x += rect.right - ball.getRect().left;
				ball.reboundX(true);
				if (ball.getVelocity().y > 0.0f)
					ballPos.y += rect.bottom - ball.getRect().top;
				else
					ballPos.y -= ball.getRect().bottom - rect.top;
				test = true;
			}
			else
			{
				//top
				ballPos.y -= ball.getRect().bottom - rect.top;
				const float relativeX = ballCurrPos.x - pos.x;
				const float bounceAngle = relativeX * (3 * float(M_PI) / 2) / (pos.x) + float(M_PI) / 2;
				ball.setDirection(Vec2(-cosf(bounceAngle), -sinf(bounceAngle)).Normalize() * BALL_SPEED);
				test = true;
			}
		}
		ballCurrPos += ballPos;
		ball.setPosition(ballCurrPos);
		if (test)
		{
			test = false;
			return true;
		}
		
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
	if ( incLength )
	{
		frames += dt;
		diff = ( ( longHalfWidth - halfWidth ) / 2 ) * 2;
	}
	else
	{
		frames = 0;
		amount = 0;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

void Paddle::lengthPwrUp()
{
	if ( longHalfWidth < maxLength )
		longHalfWidth += 5.0f;
	incLength = true;
}

void Paddle::lengthPwrUpReset( )
{
	incLength = false;
	longHalfWidth = halfWidth + 5.0f;
}

Rect Paddle::getRect() const
{
	if (incLength )
		return Rect::fromCenter(pos, longHalfWidth, halfHeight);

	return Rect::fromCenter( pos , halfWidth , halfHeight );
}

Vec2 Paddle::getVec() const
{
	return pos;
}

void Paddle::setPos(const Vec2& pos_)
{
	pos = pos_;
}
